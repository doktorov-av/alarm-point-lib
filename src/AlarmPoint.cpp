//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "AlarmPoint.hpp"

bool apl::AlarmPoint::InAlarm() const {
    return static_cast<bool>(GetAlarmState());
}
apl::AlarmPoint::AlarmProxy apl::AlarmPoint::GetAlarmState() const {
    return AlarmProxy{rules_.AnyBroken()};
}
