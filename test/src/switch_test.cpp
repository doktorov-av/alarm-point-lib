//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "gtest/gtest.h"
#include "AlarmPoint.hpp"
#include "Rules.hpp"

class SwitchTest : public apl::AlarmPoint {
public:
    [[nodiscard]] bool GetValueImpl() const { return value_; }
    bool value_ = false;
};

class SwitchFixture : public ::testing::Test {
protected:
    SwitchTest _switch{};
};

TEST_F(SwitchFixture, Alarm) {
    _switch.Apply(apl::rules::NotEqualCmp(&_switch, false));
    _switch.value_ = false;
    ASSERT_TRUE(_switch.InAlarm());
}

TEST_F(SwitchFixture, Ok) {
    _switch.Apply(apl::rules::NotEqualCmp(&_switch, false));
    _switch.value_ = true;
    ASSERT_FALSE(_switch.InAlarm());
}
