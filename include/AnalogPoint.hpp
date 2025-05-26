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
private:
    class AlarmProxy {
    public:
        explicit AlarmProxy(std::shared_ptr<IRule> brokenRule) : alarmRule_(std::move(brokenRule)) {}
        decltype(auto) GetBrokenRule() {
            return alarmRule_;
        }
        operator bool(this auto&& self) {
            return self.alarmRule_ != nullptr;
        }
    private:
        std::shared_ptr<IRule> alarmRule_;
    };
public:
    explicit AnalogPoint(unsigned int id) : id_(id) { assert(id != 0); };

    AnalogPoint() = delete;
    AnalogPoint(AnalogPoint &&) = default;
    AnalogPoint(const AnalogPoint &) = default;

    bool operator<(this auto&&self, double value) { return self.GetRbdValue() < value; }
    bool operator>(this auto&&self, double value) { return self.GetRbdValue() > value; }

    template<class Self, class V>
    bool operator<(this Self&& self, V&& other) { return self.GetRbdValue() < other.GetRbdValue(); }

    [[nodiscard]] bool InAlarm() const override;
    [[nodiscard]] AlarmProxy GetAlarmState() const;
    [[nodiscard]] double GetRbdValue() const { return value_; }

    void AddUpperBoundary(const std::shared_ptr<AnalogPoint> &otherPoint);
    void AddUpperBoundary(double value);

    void AddLowerBoundary(const std::shared_ptr<AnalogPoint> &otherPoint);
    void AddLowerBoundary(double value);

    double value_ = 0.0;
private:
    RuleSet rules_{};
    unsigned int id_;
};

APL_NAMESPACE_END

#endif //RBDANALOGPOINT_HPP
