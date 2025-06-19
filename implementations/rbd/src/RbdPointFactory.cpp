//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "RbdPointFactory.hpp"
#include "Analog.hpp"
#include "rbdlib.h"

std::unique_ptr<apl::Analog> RbdPointFactory::makeAnalog(const apl::ConfigData<apl::Falarm> &configData) const {
    unsigned int id = 0;
    auto error = mlbUNum(configData.name.c_str(), &id, nullptr);
    if(error != LIBMLB_NOERROR) {
        // @todo or throw exception
        return nullptr;
    }

    auto point = std::make_unique<Analog>(id);
    point->AddUpperBoundary(configData.alarmConfig.lower_bound);
    point->AddLowerBoundary(configData.alarmConfig.lower_bound);
    return point;
}

std::unique_ptr<apl::MultiState<int>> RbdPointFactory::makeMultiState(const apl::ConfigData<apl::Malarm> &configData) const {
    return nullptr;
}

std::unique_ptr<apl::Switch> RbdPointFactory::makeBoolean(const apl::ConfigData<apl::Dalarm> &configData) const {
    return nullptr;
}
