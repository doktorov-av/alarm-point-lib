//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_ALARMPOINTREPO_HPP
#define ALARM_POINT_LIB_ALARMPOINTREPO_HPP

#include "PointFactory.hpp"
#include "PointConfigData.hpp"

APL_NAMESPACE_BEGIN

class AlarmPointRepo {
public:
    explicit AlarmPointRepo(PointFactory& factory);
    explicit AlarmPointRepo(PointFactory& factory, const std::vector<PointConfigData>& configData);

    void Load(const std::vector<PointConfigData>& configData);
private:
    std::vector<std::unique_ptr<AlarmPoint>> _points{};
    PointFactory& factory;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_ALARMPOINTREPO_HPP
