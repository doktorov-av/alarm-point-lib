//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_RBDPOINT_HPP
#define ALARM_POINT_LIB_RBDPOINT_HPP

#include "apl/AlarmPoint.hpp"
#include "rbdlib.h"

class RbdPoint : public apl::AlarmPoint {
public:
    explicit RbdPoint(unsigned int id) : id(id) { assert(id != 0); }
    [[nodiscard]] double GetValueImpl() const {
        return mlbUVal(id);
    }
private:
    unsigned int id;
};

#endif //ALARM_POINT_LIB_RBDPOINT_HPP
