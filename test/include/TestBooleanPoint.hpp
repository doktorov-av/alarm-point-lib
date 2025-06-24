//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_TESTBOOLEANPOINT_HPP
#define ALARM_POINT_LIB_TESTBOOLEANPOINT_HPP

#include "Switch.hpp"

class TestBooleanPoint : public apl::Switch {
public:
    using apl::Switch::Switch;
    [[nodiscard]] bool GetValue() const override { return value_; }
    bool value_ = false;
};

#endif //ALARM_POINT_LIB_TESTBOOLEANPOINT_HPP
