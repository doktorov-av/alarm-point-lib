//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "AlarmPointRepo.hpp"

apl::AlarmPointRepo::AlarmPointRepo(apl::PointFactory &factory) : factory(factory) {}

apl::AlarmPointRepo::AlarmPointRepo(apl::PointFactory &factory, const std::vector<PointConfigData> &configData) :
    factory(factory) {
    Load(configData);
}

void apl::AlarmPointRepo::Load(const std::vector<PointConfigData> &configData) {
    _points.clear();
    _points.reserve(configData.size());

    for (const auto &data: configData) {
        decltype(auto) newPoint = factory.makePoint(data);
        if(!newPoint)
            continue;
        _points.emplace_back(std::move(newPoint));
    }
}
