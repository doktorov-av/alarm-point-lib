//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_RBDPOINTFACTORY_HPP
#define ALARM_POINT_LIB_RBDPOINTFACTORY_HPP

#include "RbdAnalog.hpp"
#include "apl/IPointFactory.hpp"
#include "apl/Points.hpp"

class RbdPointFactory : public apl::IPointFactory {
public:
    std::unique_ptr<apl::AlarmPoint> createAnalog(const std::string &name, const apl::Falarm &config,
                                             std::weak_ptr<apl::IPlant> plant) override;
    std::unique_ptr<apl::AlarmPoint> createSwitch(const std::string &name, const apl::Dalarm &config,
                                             std::weak_ptr<apl::IPlant> plant) override;
    std::unique_ptr<apl::AlarmPoint> createMultiState(const std::string &name, const apl::MalarmInt &config,
                                                 std::weak_ptr<apl::IPlant> plant) override;
};

#endif //ALARM_POINT_LIB_RBDPOINTFACTORY_HPP
