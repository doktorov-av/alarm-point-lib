//
// Created by Doktorov Alexander on 6/25/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_BOUNDTYPES_HPP
#define ALARM_POINT_LIB_BOUNDTYPES_HPP

#include <stdexcept>
#include <string>
#include <string_view>

APL_NAMESPACE_BEGIN

enum class EBoundType { Operational, Alarm, MaximumPossible };

EBoundType to_bound_type(const std::string &s);
std::string_view to_string_view(EBoundType type);
std::string to_string(EBoundType type);


APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_BOUNDTYPES_HPP
