//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "ModeAnalog.hpp"
#include "Rules.hpp"

apl::ModeAnalog::ModeAnalog(const std::shared_ptr<IPlant> &plant)  : AlarmPoint(std::make_unique<ModeRuleSet>(plant)) {}

void apl::ModeAnalog::AddUpperBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, apl::block_mode_t mode) {
    GetModeRules().AddModeRule(rules::Less(otherPoint, this), mode);
}
void apl::ModeAnalog::AddUpperBoundary(double value, apl::block_mode_t mode) {
    GetModeRules().AddModeRule(rules::Less(value, this), mode);
}
void apl::ModeAnalog::AddLowerBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, apl::block_mode_t mode) {
    GetModeRules().AddModeRule(rules::Greater(otherPoint, this), mode);
}
void apl::ModeAnalog::AddLowerBoundary(double value, apl::block_mode_t mode) {
    GetModeRules().AddModeRule(rules::Greater(value, this), mode);
}
apl::ModeRuleSet &apl::ModeAnalog::GetModeRules() const {
    return GetRulesAs<ModeRuleSet>();
}
