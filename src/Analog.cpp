//
// Created by DoktorovAlexander on 23.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "Analog.hpp"

#include <iostream>

#include "Rules.hpp"

APL_NAMESPACE_BEGIN

Analog::Analog(std::unique_ptr<IRuleSet> &&rules_) : AlarmPoint(std::move(rules_)) {}

rules::RuleHandle Analog::AddUpperBoundary(const std::shared_ptr<Analog> &otherPoint) {
    decltype(auto) rule = rules::Less(std::weak_ptr{otherPoint}, this);
    GetRules()->AddRule(rule);
    return rule;
}

rules::RuleHandle Analog::AddLowerBoundary(const std::shared_ptr<Analog> &otherPoint) {
    decltype(auto) rule = rules::Greater(std::weak_ptr{otherPoint}, this);
    GetRules()->AddRule(rule);
    return rule;
}

rules::RuleHandle Analog::AddUpperBoundary(double value) {
    decltype(auto) rule = rules::Less(value, this, [](const Analog *self, double bound) {
        return std::format("Lower boundary exceeded: current value = {}, bound = {}", self->GetValue(), bound);
    });
    GetRules()->AddRule(rule);
    return rule;
}

rules::RuleHandle Analog::AddLowerBoundary(double value) {
    decltype(auto) rule = rules::Greater(value, this, [](const Analog *self, double bound) {
        return std::format("Upper boundary exceeded: current = {}, bound = {}", self->GetValue(), bound);
    });
    GetRules()->AddRule(rule);
    return rule;
}


APL_NAMESPACE_END
