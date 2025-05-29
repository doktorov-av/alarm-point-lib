//
// Created by DoktorovAlexander on 23.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef RBDANALOGPOINT_HPP
#define RBDANALOGPOINT_HPP

#include "AlarmPoint.hpp"

APL_NAMESPACE_BEGIN

class Analog : public AlarmPoint {
public:
    explicit Analog(std::unique_ptr<IRuleSet>&& rules_ = std::make_unique<RuleSet>());

    [[nodiscard]] virtual double GetValue() const = 0;
    inline auto operator<=>(this auto&& self, const Analog & other) {
        return self.GetValue() <=> other.GetValue();
    }
    inline auto operator<=>(this auto&& self, double value) {
        return self.GetValue() <=> value;
    }
    void AddUpperBoundary(const std::shared_ptr<Analog> &otherPoint);
    void AddUpperBoundary(double value);

    void AddLowerBoundary(const std::shared_ptr<Analog> &otherPoint);
    void AddLowerBoundary(double value);
};

APL_NAMESPACE_END

#endif //RBDANALOGPOINT_HPP
