//
// Created by DoktorovAlexander on 23.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "AnalogPoint.hpp"
#include "Rules.hpp"

APL_NAMESPACE_BEGIN

bool apl::AnalogPoint::InAlarm() const {
    return !rules_.Follows();
}
void apl::AnalogPoint::AddUpperBoundary(double value) {
    rules_.AddRule(rules::Less(value, this));
}
void apl::AnalogPoint::AddLowerBoundary(double value) {
    rules_.AddRule(rules::Greater(value, this));
}

APL_NAMESPACE_END
