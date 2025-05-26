//
// Created by DoktorovAlexander on 23.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "AnalogPoint.hpp"
#include "Rules.hpp"

APL_NAMESPACE_BEGIN

void apl::AnalogPoint::AddUpperBoundary(double value) {
    rules_.AddRule(rules::Less(value, this, [](const apl::AnalogPoint& self, const double& bound) {
        return std::format("Lower boundary exceeded: current value = {}, bound = {}", self.GetRbdValue(), bound);
    }));
}
void apl::AnalogPoint::AddLowerBoundary(double value) {
    rules_.AddRule(rules::Greater(value, this, [](const apl::AnalogPoint& self, const double& bound) {
        return std::format("Upper boundary exceeded: current = {}, bound = {}", self.GetRbdValue(), bound);
    }));
}

AnalogPoint::AlarmProxy AnalogPoint::GetAlarmState() const {
    return AlarmProxy(rules_.AnyBroken());
}

bool AnalogPoint::InAlarm() const {
    return !rules_.Follows();
}

APL_NAMESPACE_END
