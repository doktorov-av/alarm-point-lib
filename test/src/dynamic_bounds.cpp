//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "gtest/gtest.h"
#include "TestAnalogPoint.hpp"

class DynamicBoundsFixture : public ::testing::Test  {
protected:
    void SetUp() override {
        pStatic.value_ = 0.0;
        pDynamicUpper->value_ = 10;
        pDynamicLower->value_ = -10;
        pStatic.AddUpperBoundary(pDynamicUpper);
        pStatic.AddLowerBoundary(pDynamicLower);
    }
    std::shared_ptr<TestAnalogPoint> pDynamicUpper = std::make_shared<TestAnalogPoint>();
    std::shared_ptr<TestAnalogPoint> pDynamicLower = std::make_shared<TestAnalogPoint>();
    TestAnalogPoint pStatic{};
};

TEST_F(DynamicBoundsFixture, upper) {
    pStatic.value_ = 10;
    EXPECT_TRUE(pStatic.GetAlarmState());
    pDynamicUpper->value_ = 11;
    ASSERT_FALSE(pStatic.GetAlarmState());
    pDynamicLower->value_ = pStatic.value_;
    ASSERT_TRUE(pStatic.GetAlarmState());
}

TEST_F(DynamicBoundsFixture, lower) {
    pStatic.value_ = -10;
    EXPECT_TRUE(pStatic.GetAlarmState());
    pDynamicLower->value_ = -11;
    ASSERT_FALSE(pStatic.GetAlarmState());
    pDynamicLower->value_ = pStatic.value_;
    ASSERT_TRUE(pStatic.GetAlarmState());
}

