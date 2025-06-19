//
// Created by DoktorovAlexander on 24.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef POINT_HPP
#define POINT_HPP
#include <algorithm>
#include <memory>
#include <vector>

#include "IRuleSet.hpp"

APL_NAMESPACE_BEGIN

// this class describes a composition of rules
class RuleSet : public IRuleSet {
public:
    RuleSet() = default;

    void AddRule(std::shared_ptr<IRule> rule);
    void Clear() override;
    [[nodiscard]] bool Empty() const override;

    // Finds first invalid rule
    [[nodiscard]] std::shared_ptr<IRule> AnyBroken() const override;
private:
    std::vector<std::shared_ptr<IRule>> rules;
};


APL_NAMESPACE_END

#endif //POINT_HPP
