//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "RbdPointFactory.hpp"
#include "Analog.hpp"
#include "rbdlib.h"

std::unique_ptr<apl::AlarmPoint> RbdPointFactory::makePoint(const apl::PointConfigData &configData) const {
    assert(mlbIsOK());
    return apl::PointFactory::makePoint(configData);
}

std::unique_ptr<apl::Analog> RbdPointFactory::makeAnalog(const apl::ConfigData<apl::Falarm> &configData) const {
    unsigned int id = 0;
    auto error = mlbUNum(configData.name.c_str(), &id, nullptr);
    if(error != LIBMLB_NOERROR) {
        throw std::runtime_error(std::format("Error {}: unable to create rbd point with {} name", mlbErrDescRu(error), configData.name));
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