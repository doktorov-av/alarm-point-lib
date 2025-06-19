//
// Created by DoktorovAlexander on 23.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef RBDANALOGPOINT_HPP
#define RBDANALOGPOINT_HPP

#include <utility>

#include "AlarmPoint.hpp"
#include "RuleBuilder.hpp"

APL_NAMESPACE_BEGIN

class Analog : public AlarmPoint {
public:
    using AlarmPoint::AlarmPoint;

    [[nodiscard]] virtual double GetValue() const = 0;
    inline auto operator<=>(this auto&& self, const Analog & other) {
        return self.GetValue() <=> other.GetValue();
    }
    inline auto operator<=>(this auto&& self, double value) {
        return self.GetValue() <=> value;
    }

    template<class T>
    void AddUpperBoundary(T&& bound, block_mode_t mode) {
        RuleBuilder builder(rules::Less(std::forward<T>(bound), this));
        builder.Plant(GetPlant());
        GetRules()->AddRule(builder.Build(mode));
    }

    template<class T>
    void AddUpperBoundary(T&& bound) {
        GetRules()->AddRule(rules::Less(std::forward<T>(bound), this));
    }

    template<class T>
    void AddLowerBoundary(T&& bound) {
        GetRules()->AddRule(rules::Greater(std::forward<T>(bound), this));
    }

    template<class T>
    void AddLowerBoundary(T&& bound, block_mode_t mode) {
        RuleBuilder builder(rules::Greater(std::forward<T>(bound), this));
        builder.Plant(GetPlant());
        GetRules()->AddRule(builder.Build(mode));
    }
};

APL_NAMESPACE_END

#endif //RBDANALOGPOINT_HPP
