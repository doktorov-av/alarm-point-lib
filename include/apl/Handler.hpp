//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_CHANGEHANDLER_HPP
#define ALARM_POINT_LIB_CHANGEHANDLER_HPP

#include "AlarmPoint.hpp"

APL_NAMESPACE_BEGIN

class Handler {
public:
    virtual void HandleInitialChange(AlarmPoint *alarmPoint, const AlarmState &changedTo) { };
    virtual void HandleChange(AlarmPoint *alarmPoint, const AlarmState &changedFrom, const AlarmState &changedTo) = 0;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_CHANGEHANDLER_HPP
