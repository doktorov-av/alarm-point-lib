//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "Analog.hpp"
#include "gtest/gtest.h"

class TestModeAnalog : public apl::Analog {
    using Super = apl::Analog;
public:
    using Super::Super;
    [[nodiscard]] double GetValue() const override {
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
    TestModeAnalog modeAnalog{plant};
    modeAnalog.AddUpperBoundary(10, 0);
    modeAnalog.AddLowerBoundary(-10, 0);
    ASSERT_FALSE(modeAnalog.InAlarm());
    modeAnalog.value_ = 10;
    ASSERT_TRUE(modeAnalog.InAlarm());

    plant->mode_ = 1;
    modeAnalog.AddUpperBoundary(20, plant->mode_);
    modeAnalog.AddLowerBoundary(-20, plant->mode_);
    ASSERT_FALSE(modeAnalog.InAlarm());

    plant->mode_ = 0;
    ASSERT_TRUE(modeAnalog.InAlarm());
    plant->mode_ = 1;
    ASSERT_FALSE(modeAnalog.InAlarm());
}
