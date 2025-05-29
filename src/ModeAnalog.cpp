//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "ModeAnalog.hpp"
#include "Rules.hpp"

APL_NAMESPACE_BEGIN

ModeAnalog::ModeAnalog(const std::shared_ptr<IPlant> &plant) : Analog(std::make_unique<ModeRuleSet>(plant)) {
    _modeRules = dynamic_cast<ModeRuleSet*>(GetRules());
    assert(_modeRules);
}

// ~~~~~~~~~~~~~~~~~~~~ upper bounds overloads ~~~~~~~~~~~~~~~~~~~~ //
rules::RuleHandle ModeAnalog::AddUpperBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, block_mode_t mode) {
    return AddUpperBoundaryImpl(otherPoint, mode);
}

rules::RuleHandle ModeAnalog::AddUpperBoundary(double value, block_mode_t mode) {
    return AddUpperBoundaryImpl(value, mode);
}
rules::RuleHandle ModeAnalog::AddUpperBoundary(const ModeAnalog *otherPoint) {
    return AddUpperBoundaryImpl(otherPoint);
}

// ~~~~~~~~~~~~~~~~~~~~ lower bounds overloads ~~~~~~~~~~~~~~~~~~~~ //
rules::RuleHandle ModeAnalog::AddLowerBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, block_mode_t mode) {
    return AddLowerBoundaryImpl(otherPoint, mode);
}
rules::RuleHandle ModeAnalog::AddLowerBoundary(double value, block_mode_t mode) {
    return AddLowerBoundaryImpl(value, mode);
}
rules::RuleHandle ModeAnalog::AddLowerBoundary(const ModeAnalog *&otherPoint) {
    return AddLowerBoundaryImpl(otherPoint);
}

APL_NAMESPACE_END
