//
// Created by DoktorovAlexander on 23.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "Analog.hpp"

#include <iostream>

#include "Rules.hpp"

APL_NAMESPACE_BEGIN

Analog::Analog(std::unique_ptr<IRuleSet>&& rules_) : AlarmPoint(std::move(rules_)) {

}

void Analog::AddUpperBoundary(const std::shared_ptr<Analog> &otherPoint) {
    GetRules()->AddRule(rules::Less(std::weak_ptr{otherPoint}, this));
}

void Analog::AddLowerBoundary(const std::shared_ptr<Analog> &otherPoint) {
    GetRules()->AddRule(rules::Greater(std::weak_ptr{otherPoint}, this));
}

void Analog::AddUpperBoundary(double value) {
    GetRules()->AddRule(rules::Less(value, this, [](const Analog * self, double bound) {
        return std::format("Lower boundary exceeded: current value = {}, bound = {}", self->GetValue(), bound);
    }));
}

void Analog::AddLowerBoundary(double value) {
    GetRules()->AddRule(rules::Greater(value, this, [](const Analog * self, double bound) {
        return std::format("Upper boundary exceeded: current = {}, bound = {}", self->GetValue(), bound);
    }));
}


APL_NAMESPACE_END
