//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_POINTFACTORY_HPP
#define ALARM_POINT_LIB_POINTFACTORY_HPP

#include "memory"
#include "Analog.hpp"
#include "Switch.hpp"
#include "MultiState.hpp"
#include "PointConfigData.hpp"

APL_NAMESPACE_BEGIN

class PointFactory {
public:
    [[nodiscard]] std::unique_ptr<AlarmPoint> makePoint(const PointConfigData &configData) const;
protected:
    [[nodiscard]] virtual std::unique_ptr<Analog> makeAnalog(const ConfigData<Falarm>& configData) const = 0;
    [[nodiscard]] virtual std::unique_ptr<Switch> makeBoolean(const ConfigData<Dalarm>& configData) const = 0;
    [[nodiscard]] virtual std::unique_ptr<MultiState<int>> makeMultiState(const ConfigData<Malarm>& configData) const = 0;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_POINTFACTORY_HPP
