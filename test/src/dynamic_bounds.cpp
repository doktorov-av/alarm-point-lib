//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "gtest/gtest.h"
#include "Rules.hpp"
#include "TestAnalogPoint.hpp"

class DynamicBoundsFixture : public ::testing::Test  {
protected:
    void SetUp() override {
        pStatic.value_ = 0.0;
        pDynamicUpper->value_ = 10;
        pDynamicLower->value_ = -10;
        pStatic.Apply(apl::rules::LessCmp(&pStatic, &pDynamicUpper));
        pStatic.Apply(apl::rules::GreaterCmp(&pStatic, &pDynamicLower));
    }
    std::shared_ptr<TestAnalogPoint> pDynamicUpper = std::make_shared<TestAnalogPoint>();
    std::shared_ptr<TestAnalogPoint> pDynamicLower = std::make_shared<TestAnalogPoint>();
    TestAnalogPoint pStatic{};
};

TEST_F(DynamicBoundsFixture, upper) {
    pStatic.value_ = 10;
    EXPECT_TRUE(pStatic.InAlarm());
    pDynamicUpper->value_ = 11;
    ASSERT_FALSE(pStatic.InAlarm());
    pDynamicLower->value_ = pStatic.value_;
    ASSERT_TRUE(pStatic.InAlarm());
}

TEST_F(DynamicBoundsFixture, lower) {
    pStatic.value_ = -10;
    EXPECT_TRUE(pStatic.InAlarm());
    pDynamicLower->value_ = -11;
    ASSERT_FALSE(pStatic.InAlarm());
    pDynamicLower->value_ = pStatic.value_;
    ASSERT_TRUE(pStatic.InAlarm());
}

