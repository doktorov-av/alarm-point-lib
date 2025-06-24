//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_RBDANALOG_HPP
#define ALARM_POINT_LIB_RBDANALOG_HPP

#include "apl/Analog.hpp"
#include "rbdlib.h"

class RbdAnalog : public apl::Analog {
public:
    explicit RbdAnalog(unsigned int id) : id(id) { assert(id != 0); }
    [[nodiscard]] double GetValue() const override {
        return mlbUVal(id);
    }
private:
    unsigned int id;
};

#endif //ALARM_POINT_LIB_RBDANALOG_HPP
