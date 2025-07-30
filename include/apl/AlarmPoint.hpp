//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_ALARMPOINT_HPP
#define ALARM_POINT_LIB_ALARMPOINT_HPP

#include <type_traits>
#include <utility>
#include "IAlarmable.hpp"
#include "IPlant.hpp"
#include "RuleSet.hpp"
#include "Utils.hpp"

#include "AlarmState.hpp"
#include "cassert"
APL_NAMESPACE_BEGIN

class AlarmPoint : public IAlarmable {
public:
    AlarmPoint() = default;
    explicit AlarmPoint(std::string name) : name(std::move(name)) {}

    decltype(auto) GetValue(this auto&& self) { return self.GetValueImpl(); }
    virtual void SetName(const std::string& newName) { name = newName; }
    [[nodiscard]] virtual std::string_view GetNameStrview() const { return name; }
    [[nodiscard]] virtual std::string GetName() const { return name; }

    [[nodiscard]] inline decltype(auto) GetRules() const { return rules_.get(); }
    [[nodiscard]] bool InAlarm() const override;
    [[nodiscard]] AlarmState GetAlarmState() const;

    virtual void Apply(std::shared_ptr<IRule> rule) { rules_->AddRule(std::move(rule)); }
private:
    std::unique_ptr<RuleSet> rules_ = std::make_unique<RuleSet>();
    std::string name;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_ALARMPOINT_HPP
