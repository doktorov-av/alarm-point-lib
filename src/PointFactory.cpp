//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "PointFactory.hpp"

APL_NAMESPACE_BEGIN

std::unique_ptr<AlarmPoint> PointFactory::makePoint(const PointConfigData &configData) const {
    switch (configData.type) {
        case Type::Floating: {
            const auto& data = configData.to_config_data<Falarm>();
            return makeAnalog(data);
        }
        case Type::Boolean: {
            const auto& data = configData.to_config_data<Dalarm>();
            return makeBoolean(data);
        }
        case Type::Multistate: {
            const auto& data = configData.to_config_data<Malarm>();
            return makeMultiState(data);
        }
        default: break;
    }
    return nullptr;
}

APL_NAMESPACE_END