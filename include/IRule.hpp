//
// Created by DoktorovAlexander on 23.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef IRULE_HPP
#define IRULE_HPP

#include "functional"

APL_NAMESPACE_BEGIN

class IRule {
public:
    virtual ~IRule() = default;
    [[nodiscard]] virtual bool Evaluate() const = 0;
    [[nodiscard]] virtual std::string GetFailDescription() const = 0;

    virtual void SetFailDescription(const std::string &description) = 0;
    virtual void SetFailDescription(const std::function<std::string(void)>& fn) = 0;
};

APL_NAMESPACE_END

#endif //IRULE_HPP
