//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//


#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Tracker.hpp"
#include "TestBooleanPoint.hpp"

class SimpleHandler : public apl::Handler {
public:
    MOCK_METHOD(void, HandleChange, (apl::AlarmPoint*, const apl::AlarmState&, const apl::AlarmState&));
    MOCK_METHOD(void, HandleInitialChange, (apl::AlarmPoint*, const apl::AlarmState &));
};

TEST(Tracker, detects) {
    using namespace apl;

    SimpleHandler handler{};
    Tracker tracker{handler};
    EXPECT_CALL(handler, HandleChange).Times(2);
    EXPECT_CALL(handler, HandleInitialChange).Times(1);

    TestBooleanPoint booleanPoint("name");
    tracker.Update(&booleanPoint);

    booleanPoint.SetAlarmState(true);
    booleanPoint.value_ = true;

    tracker.Update(&booleanPoint);

    booleanPoint.value_ = false;
    tracker.Update(&booleanPoint);
}