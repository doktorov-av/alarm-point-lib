//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_CONFIGDATA_HPP
#define ALARM_POINT_LIB_CONFIGDATA_HPP

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

template<class T>
struct MalarmState {
    T value = 0;
    bool prohibited = false;
    std::optional<std::string> message;
};

template<class T>
struct Malarm {
    using state_t = MalarmState<T>;
    std::unordered_map<std::string, state_t> states;
};

using MalarmInt = Malarm<int>;
using MalarmStateInt = MalarmInt::state_t;

enum class Type { Undefined, Floating, Boolean, Multistate };

using AlarmVariant = std::variant<Falarm, Dalarm, MalarmInt>;

struct ConfigData {
    template<class T>
    [[nodiscard]] decltype(auto) cast() const {
        return std::get<T>(alarm);
    }
    [[nodiscard]] std::string_view TypeString() const;
    Type type = Type::Undefined;
    AlarmVariant alarm;
};

struct PointConfigData : public ConfigData{
    std::string name;
};

Type from_string(std::string_view str);
std::string_view to_string_view(Type type);

// json parsing
void from_json(const json &j, Falarm &f);
void from_json(const json &j, Dalarm &d);
void from_json(const json &j, MalarmStateInt &state);
void from_json(const json &j, MalarmInt &malarm);
void from_json(const json &j, PointConfigData &p);

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_CONFIGDATA_HPP
