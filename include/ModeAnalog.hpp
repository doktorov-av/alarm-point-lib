//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_MODEANALOG_HPP
#define ALARM_POINT_LIB_MODEANALOG_HPP

#include "Analog.hpp"
#include "ModeRuleSet.hpp"
#include "Rules.hpp"
#include "functional"

APL_NAMESPACE_BEGIN

class ModeAnalog : public Analog {
    using Super = AlarmPoint;

public:
    explicit ModeAnalog(const std::shared_ptr<IPlant> &plant);

    inline auto operator<=> (const ModeAnalog &other) const { return GetValue() <=> other.GetValue(); }
    inline auto operator<=> (double value) const { return GetValue() <=> value; }

    rules::RuleHandle AddUpperBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, block_mode_t mode);
    rules::RuleHandle AddUpperBoundary(const ModeAnalog *otherPoint);
    rules::RuleHandle AddUpperBoundary(double value, block_mode_t mode);

    rules::RuleHandle AddLowerBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, block_mode_t mode);
    rules::RuleHandle AddLowerBoundary(const ModeAnalog *&otherPoint);
    rules::RuleHandle AddLowerBoundary(double value, block_mode_t mode);

private:
    template<typename T, typename... Args>
    decltype(auto) AddUpperBoundaryImpl(T &&threshold, Args &&...args) {
        return AddBoundary(std::forward<T>(threshold), true, std::forward<Args>(args)...);
    }
    template<typename T, typename... Args>
    decltype(auto) AddLowerBoundaryImpl(T &&threshold, Args &&...args) {
        return AddBoundary(std::forward<T>(threshold), false, std::forward<Args>(args)...);
    }
    template<typename T, typename... Args>
    decltype(auto) AddBoundary(T &&threshold, bool upper, Args &&...args) {
        std::shared_ptr<IRule> rule = nullptr;
        if(upper) {
            rule = rules::Less(std::forward<T>(threshold), this);
        } else {
            rule = rules::Greater(std::forward<T>(threshold), this);
        }
        _modeRules->AddRule(rule, std::forward<Args>(args)...);
        return rule;
    }

private:
    ModeRuleSet *_modeRules = nullptr;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_MODEANALOG_HPP
