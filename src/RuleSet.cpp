//
// Created by DoktorovAlexander on 25.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "RuleSet.hpp"

void apl::RuleSet::AddRule(std::shared_ptr<IRule> rule) {
    rules.emplace_back(std::move(rule));
}

bool apl::RuleSet::Empty() const {
    return rules.empty();
}

std::shared_ptr<apl::IRule> apl::RuleSet::AnyBroken() const {
    const auto it = std::ranges::find_if(rules, [&](const auto &rule) { return !rule->Evaluate(); });
    return it != rules.end() ? *it : nullptr;
}
