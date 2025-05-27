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
    Analog() = default;
    Analog(Analog &&) = default;
    Analog(const Analog &) = default;

    [[nodiscard]] virtual double GetValue() const = 0;

    inline auto operator<=>(const Analog & other) const {
        return GetValue() <=> other.GetValue();
    }
    inline auto operator<=>(double value) const {
        return GetValue() <=> value;
    }
    void AddUpperBoundary(const std::shared_ptr<Analog> &otherPoint);
    void AddUpperBoundary(double value);

    void AddLowerBoundary(const std::shared_ptr<Analog> &otherPoint);
    void AddLowerBoundary(double value);
};

APL_NAMESPACE_END

#endif //RBDANALOGPOINT_HPP
