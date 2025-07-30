//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "AlarmPoint.hpp"
#include "Rules.hpp"
#include "gtest/gtest.h"

class TestModeAnalog : public apl::AlarmPoint {
public:
    using apl::AlarmPoint::AlarmPoint;
    [[nodiscard]] double GetValueImpl() const {
        return value_;
    }
    double value_ = 0;
};

class TestPlant : public apl::IPlant {
public:
    [[nodiscard]] apl::block_mode_t ActiveMode() const override { return mode_; }
    apl::block_mode_t mode_ = 0;
};

TEST(ModeAnalogTest, create) {
    auto plant = std::make_shared<TestPlant>();
    TestModeAnalog modeAnalog{};
    modeAnalog.Apply(apl::rules::LessCmp(&modeAnalog, 10.0));
    modeAnalog.Apply(apl::rules::GreaterCmp(&modeAnalog, -10.0));

    ASSERT_FALSE(modeAnalog.InAlarm());

    modeAnalog.value_ = 10;
    ASSERT_TRUE(modeAnalog.InAlarm());

    modeAnalog.GetRules()->Clear();
    plant->mode_ = 1;
    modeAnalog.Apply(apl::rules::WithMode(apl::rules::LessCmp(&modeAnalog, 20.0), plant, plant->mode_));
    modeAnalog.Apply(apl::rules::WithMode(apl::rules::GreaterCmp(&modeAnalog, -20.0), plant, plant->mode_));
    ASSERT_FALSE(modeAnalog.InAlarm());

    modeAnalog.value_ = 20;
    ASSERT_TRUE(modeAnalog.InAlarm());
    modeAnalog.value_ = -20;
    ASSERT_TRUE(modeAnalog.InAlarm());
}
