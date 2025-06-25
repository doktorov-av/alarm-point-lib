//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "RbdPointFactory.hpp"
#include "RbdPoint.hpp"
#include "rbdlib.h"
#include "format"
#include "apl/RuleBuilder.hpp"

std::unique_ptr<RbdPoint> RbdPointFactory::createAnalog(const std::string &name, const apl::Falarm &config,
                                                               std::weak_ptr<apl::IPlant> plant) {
    unsigned int id = 0;
    auto error = mlbUNum(name.c_str(), &id, nullptr);
    if (error != LIBMLB_NOERROR) {
        throw std::runtime_error(
                std::format("Error {}: unable to create rbd point with {} name", mlbErrDescRu(error), name));
    }

    auto point = std::make_unique<RbdPoint>(id);
    point->Apply(apl::rules::LessCmp(point.get(), config.upper_bound));
    point->Apply(apl::rules::GreaterCmp(point.get(), config.lower_bound));
    return point;
}
std::unique_ptr<RbdPoint> RbdPointFactory::createSwitch(const std::string &name, const apl::Dalarm &config,
                                                               std::weak_ptr<apl::IPlant> plant) {
    return nullptr;
}
std::unique_ptr<RbdPoint> RbdPointFactory::createMultiState(const std::string &name,
                                                                   const apl::MalarmInt &config,
                                                                   std::weak_ptr<apl::IPlant> plant) {
    return nullptr;
}
