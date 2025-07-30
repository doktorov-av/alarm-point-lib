//
// Created by Doktorov Alexander on 6/3/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "Rules.hpp"

APL_NAMESPACE_BEGIN
namespace rules {

bool ModeWrapperRule::IsActive() const {
    if (auto plant = plant_.lock()) {
        return plant->ActiveMode() == mode_;
    }
    return false;
}

bool ModeWrapperRule::Evaluate() const {
    if(!IsActive()) // if rule is not active, it evaluates successfully
        return true;

    return wrapped_rule_->Evaluate();
}

std::string ModeWrapperRule::GetFailDescription() const {
    if (!IsActive()) {
        return "Rule inactive (wrong mode: " + std::to_string(static_cast<int>(mode_)) + ")";
    }
    return wrapped_rule_->GetFailDescription();
}
void ModeWrapperRule::Enable() {
    wrapped_rule_->Enable();
}
void ModeWrapperRule::Disable() {
    wrapped_rule_->Disable();
}

} // namespace rules
APL_NAMESPACE_END
