//
// Created by Doktorov Alexander on 6/17/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "ConfigReader.hpp"
#include "ConfigValidator.hpp"
#include "fstream"
#include "schema.hpp"

APL_NAMESPACE_BEGIN

std::vector<PointConfigData> read_config(const std::filesystem::path &path) {
    const auto& configJson = parse_config(path);
    return read_config(configJson);
}

std::vector<PointConfigData> read_config(const json &config) noexcept {
    return config.get<std::vector<PointConfigData>>();
}

json parse_config(const std::filesystem::path &configFile) {
    auto config = to_json(configFile);
    auto schema = json::parse(JSON_SCHEMA.data());
    validate(config, schema); // throws exception if validation fails
    return config;
}

json to_json(const std::filesystem::path &file) {
    auto f = std::ifstream(file);
    return json::parse(f);
}


APL_NAMESPACE_END