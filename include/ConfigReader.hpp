//
// Created by Doktorov Alexander on 6/17/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_CONFIGREADER_HPP
#define ALARM_POINT_LIB_CONFIGREADER_HPP

#include <fstream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

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

struct DataPoint {
    [[nodiscard]] std::string_view TypeString() const;
    std::string name;
    Type type = Type::Undefined;
    AlarmVariant alarm;
};

std::vector<DataPoint> read_config(const std::filesystem::path &configFile);

Type from_string(std::string_view str);
std::string_view to_string_view(Type type);

// json parsing
void from_json(const json &j, Falarm &f);
void from_json(const json &j, Dalarm &d);
void from_json(const json &j, MalarmState &state);
void from_json(const json &j, Malarm &malarm);
void from_json(const json &j, DataPoint &p);

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_CONFIGREADER_HPP
