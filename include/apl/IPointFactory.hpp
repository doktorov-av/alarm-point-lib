//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_IPOINTFACTORY_HPP
#define ALARM_POINT_LIB_IPOINTFACTORY_HPP

#include <memory>
#include <vector>
#include "AlarmPoint.hpp"
#include "ConfigData.hpp"

APL_NAMESPACE_BEGIN

template<class T>
    requires std::is_base_of_v<AlarmPoint, T>
class IPointFactory {
public:
    virtual ~IPointFactory() = default;

    virtual std::unique_ptr<T> createAnalog(const std::string &name, const Falarm &config, std::weak_ptr<IPlant> plant) = 0;
    virtual std::unique_ptr<T> createSwitch(const std::string &name, const Dalarm &config, std::weak_ptr<IPlant> plant) = 0;
    virtual std::unique_ptr<T> createMultiState(const std::string &name, const MalarmInt &config, std::weak_ptr<IPlant> plant) = 0;
    virtual std::vector<std::unique_ptr<T>> createPoints(const std::unordered_map<std::string, ConfigData> &configMap, std::weak_ptr<IPlant> plant);
};

template<class T>
    requires std::is_base_of_v<AlarmPoint, T>
std::vector<std::unique_ptr<T>> IPointFactory<T>::createPoints(const std::unordered_map<std::string, ConfigData> &configMap, std::weak_ptr<IPlant> plant) {
    std::vector<std::unique_ptr<T>> points;

    for (const auto &[name, config]: configMap) {
        std::unique_ptr<T> point;

        switch (config.type) {
            case Type::Floating:    point = createAnalog(name, std::get<Falarm>(config.alarm), plant);          break;
            case Type::Boolean:     point = createSwitch(name, std::get<Dalarm>(config.alarm), plant);          break;
            case Type::Multistate:  point = createMultiState(name, std::get<MalarmInt>(config.alarm), plant);   break;
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

#endif // ALARM_POINT_LIB_IPOINTFACTORY_HPP
