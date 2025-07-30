//
// Created by DoktorovAlexander on 23.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef IPLANT_HPP
#define IPLANT_HPP
#include "Types.hpp"

APL_NAMESPACE_BEGIN

class IPlant {
public:
    virtual ~IPlant () = default;
    [[nodiscard]] virtual block_mode_t ActiveMode() const = 0;
};

APL_NAMESPACE_END

#endif //IPLANT_HPP
