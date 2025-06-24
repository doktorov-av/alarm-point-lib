//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_IPOINTFACTORY_HPP
#define ALARM_POINT_LIB_IPOINTFACTORY_HPP

#include "AlarmPoint.hpp"
#include "ConfigData.hpp"
#include <memory>
#include <vector>

APL_NAMESPACE_BEGIN

class IPointFactory {
public:
    virtual ~IPointFactory() = default;

    virtual std::unique_ptr<AlarmPoint> createAnalog(
            const std::string& name,
            const Falarm& config,
            std::weak_ptr<IPlant> plant) = 0;

    virtual std::unique_ptr<AlarmPoint> createSwitch(
            const std::string& name,
            const Dalarm& config,
            std::weak_ptr<IPlant> plant) = 0;

    virtual std::unique_ptr<AlarmPoint> createMultiState(
            const std::string& name,
            const MalarmInt& config,
            std::weak_ptr<IPlant> plant) = 0;

    virtual std::vector<std::unique_ptr<AlarmPoint>> createPoints(
            const std::unordered_map<std::string, ConfigData>& configMap,
            std::weak_ptr<IPlant> plant);
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_IPOINTFACTORY_HPP
