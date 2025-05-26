//
// Created by DoktorovAlexander on 24.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef RULES_HPP
#define RULES_HPP

#include <format>
#include <functional>
#include <memory>

#include "IRule.hpp"
#include "numeric"
#include "utility"

APL_NAMESPACE_BEGIN

namespace rules {

namespace detail {

template<typename T>
concept formattable = requires(T & v, std::format_context ctx) {
    std::formatter<std::remove_cvref_t<T>>().format(v, ctx);
};

struct C {};
static_assert(!formattable<C>, "C should not be formattable");
static_assert(formattable<int>, "int should be formattable");

} // namespace detail


template<class T, class V, class Comp>
class Compare : public IRule {
public:
    using msg_gen_t = std::function<std::string(const V & /* value_ */, const T & /* threshold */)>;

    Compare(T threshold, const V *value) : threshold_(std::move(threshold)), value_(std::move(value)) {}

    Compare(T threshold, const V *value, msg_gen_t msgGen) : Compare(std::move(threshold), std::move(value)) {
        messageGen = std::move(msgGen);
    }

    Compare(T threshold, const V *value, std::string_view failmsg) :
        Compare(std::move(threshold), std::move(value),
                msg_gen_t([failmsg](const V &val, const T &th) { return std::string(failmsg.begin(), failmsg.end()); })) {}

    [[nodiscard]] bool Evaluate() const override { return value_ && Comp{}(*value_, threshold_); }

    [[nodiscard]] std::string GetFailDescription() const override {
        if (messageGen)
            return messageGen(*value_, threshold_);

        if constexpr (detail::formattable<T> && detail::formattable<V>) {
            return std::format("Comparison rule between for {} with threshold = {} is failed", *value_, threshold_);
        } else {
            return "Comparison rule failed";
        }
    }
private:
    T threshold_ = T{};
    const V *value_ = {};
    msg_gen_t messageGen = nullptr;
};

#define DEF_COMPARE_RULE(functionName, comparator) \
template<class T, class V, class Ret = Compare<T, V, comparator>> \
decltype(auto) functionName(T threshold, const V *value, std::string_view str = {}) { \
    return str.empty() ? std::make_shared<Ret>(std::move(threshold), value) : std::make_shared<Ret>(std::move(threshold), value, str); \
} \
template<class T, class V, class Ret = Compare<T, V, comparator>> \
decltype(auto) functionName(T threshold, const V *value, const typename Ret::msg_gen_t& msgGen) { \
    return std::make_shared<Ret>(std::move(threshold), value, msgGen); \
}

DEF_COMPARE_RULE(Less, std::less<>);
DEF_COMPARE_RULE(Greater, std::greater<>);
DEF_COMPARE_RULE(Equal, std::equal_to<>);
#undef DEF_COMPARE_RULE

} // namespace rules

APL_NAMESPACE_END

#endif //RULES_HPP
