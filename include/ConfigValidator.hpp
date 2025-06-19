//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_CONFIGVALIDATOR_HPP
#define ALARM_POINT_LIB_CONFIGVALIDATOR_HPP

#include "nlohmann/json-schema.hpp"

APL_NAMESPACE_BEGIN

using json = nlohmann::json;
using json_validator = nlohmann::json_schema::json_validator;

void validate(const json& j, const json& schema) {
    json_validator validator{};
    validator.set_root_schema(schema);
    validator.validate(j);
}

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_CONFIGVALIDATOR_HPP
