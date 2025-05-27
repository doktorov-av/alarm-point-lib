//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_ALARMPOINT_HPP
#define ALARM_POINT_LIB_ALARMPOINT_HPP

#include "IAlarmable.hpp"
#include "RuleSet.hpp"
APL_NAMESPACE_BEGIN

class AlarmPoint : public IAlarmable {
    class AlarmProxy {
    public:
        explicit AlarmProxy(std::shared_ptr<IRule> brokenRule) : alarmRule_(std::move(brokenRule)) {}
        decltype(auto) GetBrokenRule() {
            return alarmRule_;
        }
        explicit operator bool(this auto&& self) {
            return static_cast<bool>(self.alarmRule_);
        }
    private:
        std::shared_ptr<IRule> alarmRule_;
    };
public:
    [[nodiscard]] bool InAlarm() const override;
    [[nodiscard]] AlarmProxy GetAlarmState() const;
protected:
    RuleSet rules_{};
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_ALARMPOINT_HPP
