//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "gtest/gtest.h"
#include "Switch.hpp"

class SwitchTest : public apl::Switch {
public:
    [[nodiscard]] bool GetValue() const override { return value_; }
    bool value_ = false;
};

class SwitchFixture : public ::testing::Test {
protected:
    SwitchTest _switch{};
};

TEST_F(SwitchFixture, Alarm) {
    _switch.SetAlarmState(false);
    _switch.value_ = false;
    ASSERT_TRUE(_switch.InAlarm());
}

TEST_F(SwitchFixture, Ok) {
    _switch.SetAlarmState(false);
    _switch.value_ = true;
    ASSERT_FALSE(_switch.InAlarm());
}