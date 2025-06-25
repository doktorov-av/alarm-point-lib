//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_TESTANALOGPOINT_HPP
#define ALARM_POINT_LIB_TESTANALOGPOINT_HPP

#include "AlarmPoint.hpp"

class TestAnalogPoint : public apl::AlarmPoint {
public:
    [[nodiscard]] double GetValueImpl() const { return value_; }
    double value_ = 0.0;
};

#endif //ALARM_POINT_LIB_TESTANALOGPOINT_HPP
