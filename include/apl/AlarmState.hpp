//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_ALARMSTATE_HPP
#define ALARM_POINT_LIB_ALARMSTATE_HPP

#include "IRule.hpp"

APL_NAMESPACE_BEGIN

class AlarmState {
public:
    AlarmState() = default;
    explicit AlarmState(std::shared_ptr<IRule> brokenRule) : alarmRule_(std::move(brokenRule)) {}
    [[nodiscard]] decltype(auto) GetBrokenRule() const { return alarmRule_; }
    explicit operator bool(this auto &&self) { return static_cast<bool>(self.alarmRule_); }
    bool operator==(const AlarmState &other) const { return alarmRule_ == other.alarmRule_; }

private:
    std::shared_ptr<IRule> alarmRule_ = nullptr;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_ALARMSTATE_HPP
