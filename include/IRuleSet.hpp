//
// Created by DoktorovAlexander on 25.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef IRULESET_HPP
#define IRULESET_HPP

#include <memory>


#include "IRule.hpp"

APL_NAMESPACE_BEGIN

class IRuleSet {
public:
    virtual ~IRuleSet() = default;

    virtual void AddRule(std::shared_ptr<IRule> rule) = 0;
    [[nodiscard]] virtual bool Empty() const = 0;

    // Finds first broken rule and returns it's pointer
    [[nodiscard]] virtual std::shared_ptr<IRule> AnyBroken() const = 0;

    // Check if any rule is broken
    [[nodiscard]] bool Follows() const { return AnyBroken() == nullptr; }
};

APL_NAMESPACE_END

#endif //IRULESET_HPP
