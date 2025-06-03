//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_SWITCH_HPP
#define ALARM_POINT_LIB_SWITCH_HPP

#include "AlarmPoint.hpp"
APL_NAMESPACE_BEGIN

class Switch : public AlarmPoint {
public:
    using AlarmPoint::AlarmPoint;
    [[nodiscard]] virtual bool GetValue() const = 0;
    inline auto operator==(bool value) const { return GetValue() == value; }
    void SetAlarmState(bool alarmState);
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_SWITCH_HPP
