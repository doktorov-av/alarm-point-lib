//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_MULTIINT_HPP
#define ALARM_POINT_LIB_MULTIINT_HPP

#include "AlarmPoint.hpp"
#include "ConfigData.hpp"
#include "Rules.hpp"
#include "vector"

APL_NAMESPACE_BEGIN

class MultiInt : public AlarmPoint, public config_mapper<Type::Multistate> {
public:
    void AddState(int value) { allowed_.emplace_back(value); }
    void Prohibit(int value) { GetRules()->AddRule(rules::NotEqual(value, this)); }

    bool IsProhibited(int value) {
        return std::find(prohibited_.begin(), prohibited_.end(), value) != prohibited_.end();
    }

    void Configure(const json& j) override;
    virtual int GetValue() const = 0;
private:
    std::vector<int> allowed_;
    std::vector<int> prohibited_;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_MULTIINT_HPP
