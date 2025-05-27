//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_MULTISTATE_HPP
#define ALARM_POINT_LIB_MULTISTATE_HPP

#include <stdexcept>
#include <unordered_set>
#include "AlarmPoint.hpp"
#include "Rules.hpp"

APL_NAMESPACE_BEGIN

// for enums, ints, and other state-like values
template<typename T>
class MultiState : public AlarmPoint {
public:
    MultiState() = default;

    void Prohibit(const T& state);

    // Get current state value
    [[nodiscard]] virtual T GetState() const = 0;
    virtual void SetState(const T& state) = 0;

    // Runtime check for specific state (for strings)
    [[nodiscard]] bool Is(const T &state) const { return GetState() == state; }

    // Operator for rule comparisons
    bool operator==(const T &other) const { return GetState() == other; }
};

template<typename T>
class MultiState<std::basic_string<T>> : public AlarmPoint {
    using string = std::basic_string<T>;
    using string_view = std::basic_string_view<T>;
public:
    // Get current state value
    [[nodiscard]] virtual string GetState() const = 0;
    virtual void SetState(string_view state) = 0;

    void Prohibit(string_view state);

    // Runtime check for specific state (for strings)
    [[nodiscard]] bool Is(const T &state) const { return GetState() == state; }

    // Operator for rule comparisons
    bool operator==(const T &other) const { return GetState() == other; }
};

template<typename T>
void MultiState<std::basic_string<T>>::Prohibit(string_view state) {
    rules_.AddRule(rules::NotEqual(state, this));
}

template<typename T>
void MultiState<T>::Prohibit(const T &state) {
    rules_.AddRule(rules::NotEqual(state, this));
}

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_MULTISTATE_HPP
