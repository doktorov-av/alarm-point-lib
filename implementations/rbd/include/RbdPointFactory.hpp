//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_RBDPOINTFACTORY_HPP
#define ALARM_POINT_LIB_RBDPOINTFACTORY_HPP

#include "Analog.hpp"
#include "apl/PointFactory.hpp"
#include "apl/Points.hpp"

class RbdPointFactory : public apl::PointFactory {
public:
    [[nodiscard]] std::unique_ptr<apl::Analog> makeAnalog(const apl::ConfigData<apl::Falarm> &configData) const override;
    [[nodiscard]] std::unique_ptr<apl::Switch> makeBoolean(const apl::ConfigData<apl::Dalarm> &configData) const override;
    [[nodiscard]] std::unique_ptr<apl::MultiState<int>> makeMultiState(const apl::ConfigData<apl::Malarm> &configData) const override;
};

#endif //ALARM_POINT_LIB_RBDPOINTFACTORY_HPP
