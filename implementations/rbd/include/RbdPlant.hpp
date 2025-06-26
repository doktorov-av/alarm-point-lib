//
// Created by Doktorov Alexander on 6/25/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_RBDPLANT_HPP
#define ALARM_POINT_LIB_RBDPLANT_HPP

#include <format>
#include "apl/IPlant.hpp"
#include "rbdlib.h"

class RbdPlant : public apl::IPlant {
public:
    RbdPlant();
    [[nodiscard]] apl::block_mode_t ActiveMode() const override { return static_cast<apl::block_mode_t>(mlbUVal(id)); }
private:
    unsigned int id = 0;
};

#endif //ALARM_POINT_LIB_RBDPLANT_HPP
