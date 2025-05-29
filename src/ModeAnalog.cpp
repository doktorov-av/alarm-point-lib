//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "ModeAnalog.hpp"
#include "Rules.hpp"

apl::ModeAnalog::ModeAnalog(const std::shared_ptr<IPlant> &plant) : Analog(std::make_unique<ModeRuleSet>(plant)) {
    _modeRules = dynamic_cast<ModeRuleSet*>(GetRules());
    assert(_modeRules);
}

// ~~~~~~~~~~~~~~~~~~~~ upper bounds overloads ~~~~~~~~~~~~~~~~~~~~ //
void apl::ModeAnalog::AddUpperBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, apl::block_mode_t mode) {
    AddUpperBoundaryImpl(otherPoint, mode);
}
void apl::ModeAnalog::AddUpperBoundary(double value, apl::block_mode_t mode) {
    AddUpperBoundaryImpl(value, mode);
}
void apl::ModeAnalog::AddUpperBoundary(const apl::ModeAnalog *otherPoint) {
    AddUpperBoundaryImpl(otherPoint);
}

// ~~~~~~~~~~~~~~~~~~~~ lower bounds overloads ~~~~~~~~~~~~~~~~~~~~ //
void apl::ModeAnalog::AddLowerBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, apl::block_mode_t mode) {
    AddLowerBoundaryImpl(otherPoint, mode);
}
void apl::ModeAnalog::AddLowerBoundary(double value, apl::block_mode_t mode) {
    AddLowerBoundaryImpl(value, mode);
}
void apl::ModeAnalog::AddLowerBoundary(const apl::ModeAnalog *&otherPoint) {
    AddLowerBoundaryImpl(otherPoint);
}
