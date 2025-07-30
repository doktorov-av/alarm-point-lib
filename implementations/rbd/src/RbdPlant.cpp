//
// Created by Doktorov Alexander on 6/25/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "RbdPlant.hpp"

RbdPlant::RbdPlant() {
    if(auto err = mlbUNum("SYS001", &id, nullptr); err != LIBMLB_NOERROR) {
        throw std::runtime_error(std::format("Error: unable to find plant mode rbd point: {}", mlbErrDescRu(err)));
    }
}
