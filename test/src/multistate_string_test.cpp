//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "MultiState.hpp"
#include "gtest/gtest.h"

class TestMultiStateString : public apl::MultiState<std::string> {
public:
    explicit TestMultiStateString(std::string_view defaultState = {}) {
        if(!defaultState.empty())
            TestMultiStateString::AddState(std::string(defaultState.begin(), defaultState.end()));
    }
    std::string GetState() const override { return current_it_ != states_.end() ? *current_it_ : "unknown"; }
    void AddState(std::string_view state) {
        current_it_ = states_.insert(std::string(state)).first;
    }
    void SetState(std::string_view state) override {
        assert(!state.empty());
        current_it_ = states_.find(std::string(state));
    };
private:
    std::unordered_set<std::string> states_;
    decltype(states_)::iterator current_it_ = states_.end();
};

TEST(MSSTest, create) {
    constexpr std::string_view def = "def";
    TestMultiStateString multiStateString(def);
    ASSERT_EQ(multiStateString.GetState(), def);
}

TEST(MSSTest, getstate) {
    TestMultiStateString door;
    door.AddState("open");
    door.AddState("closed");
    door.SetState("open");
    ASSERT_EQ(door.GetState(), "open");
    door.SetState("closed");
    ASSERT_EQ(door.GetState(), "closed");
}

TEST(MSSTest, fail) {
    TestMultiStateString door;
    door.AddState("open");
    door.AddState("closed");
    door.SetState("kkasd-a[sd");
    ASSERT_EQ(door.GetState(), "unknown");
}