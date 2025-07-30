//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_RBDPOINTFACTORY_HPP
#define ALARM_POINT_LIB_RBDPOINTFACTORY_HPP

#include "RbdPoint.hpp"
#include "apl/IPointFactory.hpp"

class RbdPointFactory : public apl::IPointFactory<RbdPoint> {
public:
    std::unique_ptr<RbdPoint> createAnalog(const std::string &name, const apl::Falarm &config, std::weak_ptr<apl::IPlant> plant) override;
    std::unique_ptr<RbdPoint> createSwitch(const std::string &name, const apl::Dalarm &config, std::weak_ptr<apl::IPlant> plant) override;
    std::unique_ptr<RbdPoint> createMultiState(const std::string &name, const apl::MalarmInt &config, std::weak_ptr<apl::IPlant> plant) override;
};

#endif //ALARM_POINT_LIB_RBDPOINTFACTORY_HPP
