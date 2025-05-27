//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "gtest/gtest.h"
#include "MultiState.hpp"

enum class EStates { Idle, Running, Overload };
class TestMultiStateEnum : public apl::MultiState<EStates> {
public:
    [[nodiscard]] EStates GetState() const override { return current_; }
    void SetState(const EStates &state) override { current_ = state; }
private:
    EStates current_{};
};

TEST(MSENum, create) {
    TestMultiStateEnum multiState{};
    ASSERT_TRUE(multiState.Is(EStates::Idle));
    ASSERT_FALSE(multiState.Is(EStates::Running));
    ASSERT_FALSE(multiState.Is(EStates::Overload));
}

TEST(MSENum, state_change) {
    TestMultiStateEnum multiState{};
    ASSERT_TRUE(multiState.Is(EStates::Idle));
    ASSERT_FALSE(multiState.Is(EStates::Running));
    ASSERT_FALSE(multiState.Is(EStates::Overload));

    multiState.SetState(EStates::Running);
    ASSERT_TRUE(multiState.Is(EStates::Running));
}

TEST(MSENum, prohibit) {
    TestMultiStateEnum multiState{};
    multiState.SetState(EStates::Running);
    multiState.Prohibit(EStates::Running);
    ASSERT_TRUE(multiState.GetAlarmState());
    multiState.SetState(EStates::Idle);
    ASSERT_FALSE(multiState.GetAlarmState());
    multiState.Prohibit(EStates::Idle);
    ASSERT_TRUE(multiState.GetAlarmState());
}


