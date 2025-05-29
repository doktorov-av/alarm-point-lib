//
// Created by DoktorovAlexander on 25.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "ModeRuleSet.hpp"
#include "Rules.hpp"

APL_NAMESPACE_BEGIN

void ModeRuleSet::AddRule(std::shared_ptr<IRule> rule) {
    generalRules_.AddRule(std::move(rule));
}

void ModeRuleSet::AddRule(std::shared_ptr<IRule> rule, block_mode_t mode) {
    modeEntries_.emplace_back(std::move(rule), mode);
}

std::shared_ptr<IRule> ModeRuleSet::AnyBroken() const {
    // check general rules first
    if (auto ptr = AnyGeneralBroken()) {
        return ptr;
    }
    return AnyModeBroken();
}

std::shared_ptr<IRule> ModeRuleSet::AnyGeneralBroken() const {
    return generalRules_.AnyBroken();
}

[[maybe_unused]] std::shared_ptr<IRule> ModeRuleSet::AnyModeBroken() const {
    // check mode-specific rules then
    const auto strong = plant_.lock();
    if (!strong) // @todo handle plant invalid state ? (no plant, no rules are broken?)
        return nullptr;

    const auto activeMode = strong->ActiveMode();
    // find first rule that is broken
    const auto it = std::ranges::find_if(modeEntries_, [&activeMode](const auto &entry) {
        return entry.mode_ == activeMode && !entry.rule_->Evaluate();
    });
    return it != modeEntries_.end() ? it->rule_ : nullptr;
}

bool ModeRuleSet::Empty() const {
    return generalRules_.Empty() && modeEntries_.empty();
}

void ModeRuleSet::Clear() {
    generalRules_.Clear();
    modeEntries_.clear();
}

APL_NAMESPACE_END
