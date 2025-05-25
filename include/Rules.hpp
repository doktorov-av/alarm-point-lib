//
// Created by DoktorovAlexander on 24.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef RULES_HPP
#define RULES_HPP

#include <functional>
#include <memory>

#include "IRule.hpp"
#include "numeric"
#include "utility"

APL_NAMESPACE_BEGIN

namespace rules {

template<class T, class V, class Comp>
class Compare : public IRule {
public:
    explicit Compare(T thresehold, const V* value) :
        thresehold_(std::move(thresehold)), value_(std::move(value)) {}

    [[nodiscard]] bool Evaluate() const override {
        return value_ ? Comp{}(*value_, thresehold_) : false;
    }
private:
    T thresehold_ = T{};
    const V* value_ = {};
};

template<class T, class V>
decltype(auto) Less(T thresehold, const V* value) {
    using less_t = Compare<T, V, std::less<>>;
    return std::make_shared<less_t>(std::move(thresehold), value);
}

template<class T, class V>
decltype(auto) Greater(T thresehold, const V* value) {
using greater_t = Compare<T, V, std::greater<>>;
    return std::make_shared<greater_t>(std::move(thresehold), value);
}

template<class T, class V>
decltype(auto) Equal(T thresehold, const V* value) {
    using equal_t = Compare<T, V, std::equal_to<>>;
    return std::make_shared<equal_t>(std::move(thresehold), value);
}

}; // namespace rules

APL_NAMESPACE_END

#endif //RULES_HPP
