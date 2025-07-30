//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_TRACKER_HPP
#define ALARM_POINT_LIB_TRACKER_HPP

#include "AlarmPoint.hpp"
#include "Handler.hpp"

APL_NAMESPACE_BEGIN

class Tracker {
public:
    explicit Tracker(Handler& handler) : handler(handler) {};
    void Update(AlarmPoint* point);
    std::optional<AlarmState> GetLastState(const std::string& name);
private:
    // previous states
    std::unordered_map<std::string, AlarmState> states_;
    Handler& handler;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_TRACKER_HPP