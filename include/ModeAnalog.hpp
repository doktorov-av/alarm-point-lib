//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_MODEANALOG_HPP
#define ALARM_POINT_LIB_MODEANALOG_HPP

#include "ModeRuleSet.hpp"
#include "Rules.hpp"
#include "functional"
#include "Analog.hpp"

APL_NAMESPACE_BEGIN

class ModeAnalog : public Analog {
    using Super = AlarmPoint;
public:
    explicit ModeAnalog(const std::shared_ptr<IPlant> &plant);

    inline auto operator<=> (const ModeAnalog &other) const { return GetValue() <=> other.GetValue(); }
    inline auto operator<=> (double value) const { return GetValue() <=> value; }

    void AddUpperBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, block_mode_t mode);
    void AddUpperBoundary(const ModeAnalog *otherPoint);
    void AddUpperBoundary(double value, block_mode_t mode);

    void AddLowerBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, block_mode_t mode);
    void AddLowerBoundary(const ModeAnalog *&otherPoint);
    void AddLowerBoundary(double value, block_mode_t mode);
private:
    template<typename T, typename... Args>
    void AddUpperBoundaryImpl(T &&threshold, Args &&...args) {
        AddBoundary(std::forward<T>(threshold), true, std::forward<Args>(args)...);
    }
    template<typename T, typename... Args>
    void AddLowerBoundaryImpl(T &&threshold, Args &&...args) {
        AddBoundary(std::forward<T>(threshold), false, std::forward<Args>(args)...);
    }
    template<typename T, typename... Args>
    void AddBoundary(T &&threshold, bool upper, Args &&...args) {
        upper ? _modeRules->AddRule(rules::Less(std::forward<T>(threshold), this), std::forward<Args>(args)...)
              : _modeRules->AddRule(rules::Greater(std::forward<T>(threshold), this), std::forward<Args>(args)...);
    }
private:
    ModeRuleSet* _modeRules = nullptr;
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_MODEANALOG_HPP
