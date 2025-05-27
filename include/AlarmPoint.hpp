//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_ALARMPOINT_HPP
#define ALARM_POINT_LIB_ALARMPOINT_HPP

#include "IAlarmable.hpp"
#include "RuleSet.hpp"
#include "Utils.hpp"
#include <type_traits>
#include <utility>
#include "cassert"
APL_NAMESPACE_BEGIN

class AlarmPoint : public IAlarmable {
    class AlarmProxy {
    public:
        AlarmProxy() = default;
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
    explicit AlarmPoint(std::unique_ptr<IRuleSet>&& rules = std::make_unique<RuleSet>()) : rules_(std::move(rules)) {}
    [[nodiscard]] bool InAlarm() const override;
    [[nodiscard]] AlarmProxy GetAlarmState() const;
protected:
    template<class T>
    inline decltype(auto) GetRulesAs() const {
        return *dynamic_cast<T*>(rules_.get());
    }
    inline decltype(auto) GetRules(this auto&& self) { assert(self.rules_); return *self.rules_; }
private:
    std::unique_ptr<IRuleSet> rules_;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_ALARMPOINT_HPP
