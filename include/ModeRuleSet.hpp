//
// Created by DoktorovAlexander on 25.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef MODEPOINT_HPP
#define MODEPOINT_HPP

#include "IPlant.hpp"
#include "RuleSet.hpp"
#include <Types.hpp>

APL_NAMESPACE_BEGIN

class ModeRuleSet : public IRuleSet {
public:
    explicit ModeRuleSet(const std::shared_ptr<IPlant> &plant) : plant_(plant) {}

    [[nodiscard]] bool Empty() const override;
    void AddModeRule(std::shared_ptr<IRule> rule, block_mode_t mode);
    void AddRule(std::shared_ptr<IRule> rule) override;
    void Clear() override;
    [[nodiscard]] std::shared_ptr<IRule> AnyBroken() const override;
protected:
    [[nodiscard]] std::shared_ptr<IRule> AnyGeneralBroken() const;
    [[nodiscard]] std::shared_ptr<IRule> AnyModeBroken() const;
private:
    struct ModeEntry {
        std::shared_ptr<IRule> rule_ = nullptr;
        block_mode_t mode_ = {};
    };
    // mode-specific rules
    std::vector<ModeEntry> modeEntries_{};
    // rules for any modes
    RuleSet generalRules_;
    // reference to plant
    std::weak_ptr<IPlant> plant_ = {};
};


APL_NAMESPACE_END

#endif //MODEPOINT_HPP
