//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_ALARMPOINT_HPP
#define ALARM_POINT_LIB_ALARMPOINT_HPP

#include <type_traits>
#include <utility>
#include "IAlarmable.hpp"
#include "RuleSet.hpp"
#include "Utils.hpp"
#include "cassert"
APL_NAMESPACE_BEGIN

class AlarmPoint : public IAlarmable {
    class AlarmProxy {
    public:
        AlarmProxy() = default;
        explicit AlarmProxy(std::shared_ptr<IRule> brokenRule) : alarmRule_(std::move(brokenRule)) {}
        decltype(auto) GetBrokenRule() { return alarmRule_; }
        explicit operator bool(this auto &&self) { return static_cast<bool>(self.alarmRule_); }

    private:
        std::shared_ptr<IRule> alarmRule_;
    };

public:
    explicit AlarmPoint(std::unique_ptr<IRuleSet> &&rules = std::make_unique<RuleSet>()) : rules_(std::move(rules)) {}
    AlarmPoint() = default;

    void SetRules(std::unique_ptr<IRuleSet> &&newRules) { rules_ = std::move(newRules); }
    [[nodiscard]] inline decltype(auto) GetRules() const { return rules_.get(); }
    [[nodiscard]] bool InAlarm() const override;
    [[nodiscard]] AlarmProxy GetAlarmState() const;

private:
    std::unique_ptr<IRuleSet> rules_ = nullptr;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_ALARMPOINT_HPP
