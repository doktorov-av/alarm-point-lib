//
// Created by DoktorovAlexander on 23.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef IRULE_HPP
#define IRULE_HPP

#include "Types.hpp"

APL_NAMESPACE_BEGIN

class IRule {
public:
    virtual ~IRule() = default;
    [[nodiscard]] virtual bool Evaluate() const = 0;
    [[nodiscard]] virtual std::string GetFailDescription() const = 0;

    [[nodiscard]] virtual bool IsActive() const = 0;
    virtual void Enable() = 0;
    virtual void Disable() = 0;
};

APL_NAMESPACE_END

#endif //IRULE_HPP
