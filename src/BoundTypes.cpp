//
// Created by Doktorov Alexander on 6/26/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "BoundTypes.hpp"

APL_NAMESPACE_BEGIN

EBoundType to_bound_type(const std::string &s) {
    if (s == "operational")
        return EBoundType::Operational;
    if (s == "alarm")
        return EBoundType::Alarm;
    if (s == "max-possible")
        return EBoundType::MaximumPossible;
    throw std::runtime_error("Invalid bound type: " + s);
}

std::string_view to_string_view(EBoundType type) {
    switch (type) {
        case EBoundType::Operational: return "operational";
        case EBoundType::Alarm: return "alarm";
        case EBoundType::MaximumPossible: return "max-possible";
        default: throw std::runtime_error("Invalid EBoundType");
    }
}
std::string to_string(EBoundType type) {
    return std::string{to_string_view(type)};
}

APL_NAMESPACE_END
