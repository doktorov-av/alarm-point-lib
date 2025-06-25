//
// Created by DoktorovAlexander on 24.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef RULES_HPP
#define RULES_HPP

#include <format>
#include <functional>
#include <memory>
#include <utility>

#include "IPlant.hpp"
#include "IRule.hpp"
#include "utility"

APL_NAMESPACE_BEGIN

namespace rules {

namespace details {

template<typename T>
concept formattable = requires(T &v, std::format_context ctx) { std::formatter<std::remove_cvref_t<T>>().format(v, ctx); };

struct C {};
static_assert(!formattable<C>, "C should not be formattable");
static_assert(formattable<int>, "int should be formattable");

template<typename T>
struct ValueAccessor {
    static auto Get(const T &value) -> const T & { return value; }
    static bool IsValid(const T &) { return true; }
};

// Specialization for raw pointers (e.g., Analog*)
template<typename T>
struct ValueAccessor<T *> {
    static decltype(auto) Get(T *value) {
        return ValueAccessor<T>::Get(*value); // Dereference and recurse
    }
    static bool IsValid(T *value) { return value && ValueAccessor<T>::IsValid(*value); }
};

// Specialization for std::weak_ptr
template<typename T>
struct ValueAccessor<std::weak_ptr<T>> {
    static decltype(auto) Get(const std::weak_ptr<T> &value) {
        return ValueAccessor<T>::Get(*value.lock()); // Lock, dereference, and recurse
    }
    static bool IsValid(const std::weak_ptr<T> &value) { return !value.expired() && ValueAccessor<T>::IsValid(*value.lock()); }
};

// Specialization for std::shared_ptr
template<typename T>
struct ValueAccessor<std::shared_ptr<T>> {
    static decltype(auto) Get(const std::shared_ptr<T> &value) {
        return ValueAccessor<T>::Get(*value.get()); // dereference and recurse
    }
    static bool IsValid(const std::shared_ptr<T> &value) { return value && ValueAccessor<T>::IsValid(*value.get()); }
};

template<typename T>
concept HasGetValue = requires(T &&t) {
    { t.GetValue() };
};

// Specialization for types with GetValue function
template<HasGetValue T>
struct ValueAccessor<T> {
    static constexpr decltype(auto) Get(const T &t) { return t.GetValue(); }
    static constexpr bool IsValid(const T &value) {
        using invoke_result = decltype(std::declval<T>().GetValue());
        if constexpr (std::is_pointer_v<invoke_result>) {
            return static_cast<bool>(value.GetValue());
        }
        return true;
    }
};

// Helper functions to strip references/cv-qualifiers
template<typename T>
constexpr decltype(auto) Get(T &&val) {
    using CleanT = std::remove_cvref_t<T>;
    return ValueAccessor<CleanT>::Get(std::forward<T>(val));
}

template<typename T>
constexpr bool IsValid(T &&val) {
    using CleanT = std::remove_cvref_t<T>;
    return ValueAccessor<CleanT>::IsValid(std::forward<T>(val));
}

template<class T>
using get_type_t = decltype(Get(std::declval<T>()));

static_assert(std::is_same_v<get_type_t<std::weak_ptr<int>>, const int &>);
static_assert(std::is_same_v<get_type_t<int *>, const int &>);

// Tests
struct _test_ {
    [[nodiscard]] constexpr bool GetValue() const { return false; }
};

static_assert(HasGetValue<_test_>);
static_assert(Get(_test_{}) == false);
static_assert(IsValid(_test_{}) == true);

} // namespace details

class Rule : public IRule {
public:
    ~Rule() override = default;

    [[nodiscard]] bool IsActive() const override { return bActive_; }
    void Disable() override { bActive_ = false; }
    void Enable() override { bActive_ = true; }

private:
    bool bActive_ = true;
};

class ModeWrapperRule : public IRule {
    using Super = IRule;

public:
    ModeWrapperRule(std::shared_ptr<IRule> rule, std::weak_ptr<IPlant> plant, block_mode_t mode) :
        wrapped_rule_(std::move(rule)), plant_(std::move(plant)), mode_(mode) {}

    [[nodiscard]] bool IsActive() const override;
    [[nodiscard]] bool Evaluate() const override;
    [[nodiscard]] std::string GetFailDescription() const override;

    void Enable() override;
    void Disable() override;

private:
    std::shared_ptr<IRule> wrapped_rule_;
    std::weak_ptr<IPlant> plant_;
    block_mode_t mode_;
};

template<class T, class V, class Comp>
class CompareRule : public Rule {
public:
    using msg_gen_t = std::function<std::string(const V & /* value_ */, const T & /* threshold */)>;

    CompareRule() = default;

    CompareRule(T threshold, V value) : threshold_(threshold), value_(value) {}

    CompareRule(T threshold, V value, msg_gen_t msgGen) : CompareRule(threshold, value) { messageGen_ = std::move(msgGen); }

    CompareRule(T threshold, V value, std::string_view failmsg) :
        CompareRule(threshold, value,
                    failmsg.empty() ? msg_gen_t{} : msg_gen_t([failmsg](const V & /* value_ */, const T & /* threshold */) { return std::string(failmsg); })) {}


    [[nodiscard]] bool Evaluate() const override {
        if (!IsActive())
            return false;

        bool bTV = details::IsValid(threshold_);
        bool bVV = details::IsValid(value_);
        if (!(bTV && bVV)) {
            return false;
        }
        return Comp()(details::Get(value_), details::Get(threshold_));
    }

    [[nodiscard]] std::string GetFailDescription() const override {
        if (messageGen_) {
            return messageGen_(value_, threshold_);
        }
        return "Comparison rule failed";
    }

    void SetThreshold(T &&threshold) { threshold_ = std::move(threshold); }
    void SetValue(V &&value) { value_ = std::move(value); }

private:
    T threshold_;
    V value_;
    msg_gen_t messageGen_ = nullptr;
};

// Returns wrapped rule with mode support
inline std::shared_ptr<IRule> WithMode(std::shared_ptr<IRule> rule, std::weak_ptr<IPlant> plant, block_mode_t mode) {
    return std::make_shared<ModeWrapperRule>(std::move(rule), std::move(plant), mode);
}

#define DEF_COMPARE_RULE(functionName, comparator)                                                                                          \
    template<class T, class V, class Msg = std::string_view>                                                                                \
    decltype(auto) functionName(T threshold, V value, Msg &&msg = {}) {                                                                     \
        return std::make_shared<CompareRule<T, V, comparator>>(std::forward<T>(threshold), std::forward<V>(value), std::forward<Msg>(msg)); \
    }

DEF_COMPARE_RULE(Less, std::less<>);
DEF_COMPARE_RULE(Greater, std::greater<>);
DEF_COMPARE_RULE(Equal, std::equal_to<>);
DEF_COMPARE_RULE(NotEqual, std::not_equal_to<>);

#undef DEF_COMPARE_RULE

template<class V, class T, class Comp>
class CompRule : public Rule {
public:
    CompRule(V value, T thersehold) : value_(std::move(value)), threshold_(std::move(thersehold)) {}

    [[nodiscard]] bool Evaluate() const override {
        if (!IsActive())
            return false;

        bool bTV = details::IsValid(threshold_);
        bool bVV = details::IsValid(value_);
        if (!(bTV && bVV)) {
            return false;
        }
        return Comp()(details::Get(value_), details::Get(threshold_));
    }

    [[nodiscard]] std::string GetFailDescription() const override {
        if(details::IsValid(threshold_))
            return std::format("comparison rule failed, threshold = {}", details::Get(threshold_));
        return "comparison rule failed";
    }

private:
    const V value_ = nullptr;
    T threshold_;
};

#define MAKE_COMP_RULE(functionName, comparator)                                                                 \
    template<class T, class V>                                                                                   \
    decltype(auto) functionName(V value, T threshold) {                                                          \
        return std::make_shared<CompRule<V, T, comparator>>(std::forward<V>(value), std::forward<T>(threshold)); \
    }

MAKE_COMP_RULE(LessCmp, std::less<>);
MAKE_COMP_RULE(GreaterCmp, std::greater<>);
MAKE_COMP_RULE(NotEqualCmp, std::not_equal_to<>);

template<class T>
void Apply(T &&holder, std::shared_ptr<IRule> rule) {
    holder.GetRules()->AddRule(std::move(rule));
}

}; // namespace rules

APL_NAMESPACE_END

#endif //RULES_HPP
