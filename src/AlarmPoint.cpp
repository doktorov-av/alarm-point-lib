//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "AlarmPoint.hpp"

APL_NAMESPACE_BEGIN

bool AlarmPoint::InAlarm() const {
    return static_cast<bool>(GetAlarmState());
}

AlarmPoint::AlarmProxy AlarmPoint::GetAlarmState() const {
    return rules_ ? AlarmProxy{rules_->AnyBroken()} : AlarmProxy();
}

APL_NAMESPACE_END
