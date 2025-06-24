//
// Created by Doktorov Alexander on 6/17/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_CONFIGREADER_HPP
#define ALARM_POINT_LIB_CONFIGREADER_HPP

#include "ConfigData.hpp"
#include "filesystem"

APL_NAMESPACE_BEGIN

std::unordered_map<std::string, apl::ConfigData> read_config(const std::filesystem::path &path);
std::unordered_map<std::string, apl::ConfigData> read_config(const json &config) noexcept;
json parse_config(const std::filesystem::path &configFile);
json to_json(const std::filesystem::path &file);

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_CONFIGREADER_HPP
