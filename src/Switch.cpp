//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "Switch.hpp"
#include "Rules.hpp"

APL_NAMESPACE_BEGIN

Switch::Switch(std::unique_ptr<IRuleSet> &&rules) : AlarmPoint(std::move(rules)) {}

void Switch::SetAlarmState(bool alarmState) {
    GetRules()->Clear();
    GetRules()->AddRule(rules::NotEqual(alarmState, this));
}


APL_NAMESPACE_END
