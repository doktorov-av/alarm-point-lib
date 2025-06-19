//
// Created by Doktorov Alexander on 6/3/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_RULEBUILDER_HPP
#define ALARM_POINT_LIB_RULEBUILDER_HPP

#include "IPlant.hpp"
#include "IRule.hpp"
#include "Rules.hpp"
#include "memory"
APL_NAMESPACE_BEGIN

class RuleBuilder {
public:
    RuleBuilder() = default;
    explicit RuleBuilder(std::shared_ptr<IRule> baseRule) : _resultRule(std::move(baseRule)) {};
    explicit RuleBuilder(std::weak_ptr<IPlant> plant) : _plant(std::move(plant)) {};

    void Plant(std::weak_ptr<IPlant> plant) { _plant = std::move(plant); }
    [[nodiscard]] std::shared_ptr<IRule> Build(block_mode_t mode) const {
        return rules::WithMode(_resultRule, _plant, mode);
    }
    [[nodiscard]] std::shared_ptr<IRule> Build() const { return _resultRule; }
private:
    std::shared_ptr<IRule> _resultRule = nullptr;
    std::weak_ptr<IPlant> _plant = {};
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_RULEBUILDER_HPP
