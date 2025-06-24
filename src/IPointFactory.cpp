//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "IPointFactory.hpp"

APL_NAMESPACE_BEGIN

std::vector<std::unique_ptr<AlarmPoint>> IPointFactory::createPoints(
        const std::unordered_map<std::string, ConfigData> &configMap, std::weak_ptr<IPlant> plant) {
    std::vector<std::unique_ptr<AlarmPoint>> points;

    for (const auto &[name, config]: configMap) {
        std::unique_ptr<AlarmPoint> point;

        switch (config.type) {
            case Type::Floating: point = createAnalog(name, std::get<Falarm>(config.alarm), plant); break;
            case Type::Boolean: point = createSwitch(name, std::get<Dalarm>(config.alarm), plant); break;
            case Type::Multistate: point = createMultiState(name, std::get<MalarmInt>(config.alarm), plant); break;
            default:
                // Handle unknown types
                break;
        }

        if (point) {
            point->SetName(name);
            points.push_back(std::move(point));
        }
    }

    return points;
}

APL_NAMESPACE_END
