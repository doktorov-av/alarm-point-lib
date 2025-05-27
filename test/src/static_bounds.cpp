//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "TestAnalogPoint.hpp"
#include "gtest/gtest.h"

class BoundsFixture : public ::testing::TestWithParam<std::tuple<double /* value */, bool /* alarm? */>>  {
protected:
    void SetUp() override {
        point.value_ = 0.0;
        point.AddUpperBoundary(10);
        point.AddLowerBoundary(-10);
    }
    TestAnalogPoint point{};
};

TEST_P(BoundsFixture, upper_equal) {
    point.value_ = std::get<0>(GetParam());
    ASSERT_EQ(static_cast<bool>(point.GetAlarmState()), std::get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
        BoundsCheck,
        BoundsFixture,
        ::testing::Values(
                std::make_tuple(9.99, false),
                std::make_tuple(-9.99, false),
                std::make_tuple(10, true),
                std::make_tuple(11, true),
                std::make_tuple(-10, true),
                std::make_tuple(-11, true),
                std::make_tuple(0, false),
                std::make_tuple(-9, false),
                std::make_tuple(-9, false)));
