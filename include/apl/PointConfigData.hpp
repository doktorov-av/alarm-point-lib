//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_POINTCONFIGDATA_HPP
#define ALARM_POINT_LIB_POINTCONFIGDATA_HPP

#include "nlohmann/json.hpp"
#include "optional"
#include "string"
#include "variant"
#include "vector"

APL_NAMESPACE_BEGIN

using json = nlohmann::json;

struct Falarm {
    double upper_bound;
    double lower_bound;
};

struct Dalarm {
    bool alarm_state;
};

struct MalarmState {
    std::string name;
    int value = 0;
    bool prohibited = false;
    std::optional<std::string> message;
};

struct Malarm {
    std::vector<MalarmState> states;
};

enum class Type { Undefined, Floating, Boolean, Multistate };

using AlarmVariant = std::variant<Falarm, Dalarm, Malarm>;

template<class T>
struct ConfigData {
    std::string name;
    Type type = Type::Undefined;
    T alarmConfig;
};

struct PointConfigData {
    [[nodiscard]] std::string_view TypeString() const;

    template<class T>
    [[nodiscard]] decltype(auto) to_config_data() const {
        auto result = ConfigData<T>();
        result.alarmConfig = std::get<T>(alarm);
        result.type = type;
        result.name = name;
        return result;
    }

    std::string name;
    Type type = Type::Undefined;
    AlarmVariant alarm;
};

Type from_string(std::string_view str);
std::string_view to_string_view(Type type);

// json parsing
void from_json(const json &j, Falarm &f);
void from_json(const json &j, Dalarm &d);
void from_json(const json &j, MalarmState &state);
void from_json(const json &j, Malarm &malarm);
void from_json(const json &j, PointConfigData &p);

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_POINTCONFIGDATA_HPP
