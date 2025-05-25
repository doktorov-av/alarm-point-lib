//
// Created by DoktorovAlexander on 23.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef RBDANALOGPOINT_HPP
#define RBDANALOGPOINT_HPP
#include <cassert>
#include <chrono>

#include "IAlarmable.hpp"
#include "ModeRuleSet.hpp"

APL_NAMESPACE_BEGIN

class AnalogPoint : public IAlarmable {
public:
    using tp = std::chrono::system_clock::time_point;

public:
    explicit AnalogPoint(unsigned int id) : id_(id) { assert(id != 0); };

    AnalogPoint() = delete;
    AnalogPoint(AnalogPoint &&) = default;
    AnalogPoint(const AnalogPoint &) = default;

    bool operator<(this auto &&self, auto &&value) { return self.GetRbdValue() < value; }
    bool operator>(this auto &&self, auto &&value) { return self.GetRbdValue() > value; }

    bool InAlarm() const override;
    void AddUpperBoundary(double value);
    void AddLowerBoundary(double value);

    [[nodiscard]] double GetRbdValue() const { return value; }
    double value = 0.0;
private:
    RuleSet rules_{};
    unsigned int id_;
};

APL_NAMESPACE_END

#endif //RBDANALOGPOINT_HPP
