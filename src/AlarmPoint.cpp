//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "AlarmPoint.hpp"

APL_NAMESPACE_BEGIN

bool AlarmPoint::InAlarm() const {
    return static_cast<bool>(GetAlarmState());
}

AlarmState AlarmPoint::GetAlarmState() const {
    return rules_ ? AlarmState{rules_->AnyBroken()} : AlarmState();
}

APL_NAMESPACE_END
