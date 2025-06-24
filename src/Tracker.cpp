//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "Tracker.hpp"

void apl::Tracker::Update(apl::AlarmPoint *point) {
    const auto name = point->GetName();

    auto it = states_.find(name);
    if(it == states_.end()) {
        handler.HandleInitialChange(point, point->GetAlarmState());
        states_[name] = point->GetAlarmState();
        return;
    }

    auto currentState = point->GetAlarmState();
    auto previousState = it->second;

    if (!(previousState == currentState)) {
        handler.HandleChange(point, previousState, currentState);
        states_[name] = point->GetAlarmState();
    }
}

std::optional<apl::AlarmState> apl::Tracker::GetLastState(const std::string& name) {
    if(auto it = states_.find(name); it != states_.end()) {
        return it->second;
    }
    return std::nullopt;
}
