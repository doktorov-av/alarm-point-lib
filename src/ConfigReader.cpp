//
// Created by Doktorov Alexander on 6/17/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "ConfigReader.hpp"
#include "ConfigValidator.hpp"

APL_NAMESPACE_BEGIN

std::vector<DataPoint> read_config(const std::filesystem::path &path, const std::filesystem::path &schema) {
    const auto& configJson = parse_config(path, schema);
    return read_config(configJson);
}

std::vector<DataPoint> read_config(const json &config) noexcept {
    return config.get<std::vector<DataPoint>>();
}

json parse_config(const std::filesystem::path &configFile, const std::filesystem::path &configSchema) {
    auto config = to_json(configFile);
    auto schema = to_json(configSchema);
    validate(config, schema); // throws exception if validation fails
    return config;
}

json to_json(const std::filesystem::path &file) {
    auto f = std::ifstream(file);
    return json::parse(f);
}

void from_json(const json &j, DataPoint &p) {
    j.at("name").get_to(p.name);

    const auto typeStr = j.at("point_type").get<std::string>();
    p.type = from_string(typeStr);

    switch (p.type) {
        case Type::Floating: {
            p.alarm = j.at("Falarm").get<Falarm>();
            break;
        }
        case Type::Boolean: {
            p.alarm = j.at("Dalarm").get<Dalarm>();
            break;
        }
        case Type::Multistate: {
            Malarm malarm;
            j.at("Malarm").get_to(malarm.states);
            p.alarm = malarm;
            break;
        }
        default: break;
    }
}

void from_json(const json &j, Malarm &malarm) {
    j.get_to(malarm.states);
}

void from_json(const json &j, MalarmState &state) {
    j.at("name").get_to(state.name);
    j.at("value").get_to(state.value);
    j.at("prohibited").get_to(state.prohibited);
    if (j.contains("message")) {
        state.message = j["message"].get<std::string>();
    }
}

void from_json(const json &j, Dalarm &d) {
    j.at("alarm_state").get_to(d.alarm_state);
}

void from_json(const json &j, Falarm &f) {
    j.at("upper_bound").get_to(f.upper_bound);
    j.at("lower_bound").get_to(f.lower_bound);
}

Type from_string(std::string_view str) {
    if (str == "multi-state") {
        return Type::Multistate;
    } else if (str == "floating") {
        return Type::Floating;
    } else if (str == "boolean") {
        return Type::Boolean;
    }
    return Type::Undefined;
}
std::string_view to_string_view(Type type) {
    switch (type) {
        case Type::Undefined:   return "undefined";
        case Type::Floating:    return "floating";
        case Type::Boolean:     return "boolean";
        case Type::Multistate:  return "multi-state";
    }
    return "";
}

APL_NAMESPACE_END
std::string_view apl::DataPoint::TypeString() const {
    return to_string_view(type);
}
