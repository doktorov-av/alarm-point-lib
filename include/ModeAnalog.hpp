//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_MODEANALOG_HPP
#define ALARM_POINT_LIB_MODEANALOG_HPP


#include "AlarmPoint.hpp"
#include "ModeRuleSet.hpp"
APL_NAMESPACE_BEGIN

class ModeAnalog : public AlarmPoint {
    [[nodiscard]] inline ModeRuleSet& GetModeRules() const;
public:
    explicit ModeAnalog(const std::shared_ptr<IPlant>& plant);

    [[nodiscard]] virtual double GetValue() const = 0;

    inline auto operator<=>(const ModeAnalog& other) const {
        return GetValue() <=> other.GetValue();
    }
    inline auto operator<=>(double value) const {
        return GetValue() <=> value;
    }
    void AddUpperBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, block_mode_t mode);
    void AddUpperBoundary(double value, block_mode_t mode);

    void AddLowerBoundary(const std::shared_ptr<ModeAnalog> &otherPoint, block_mode_t mode);
    void AddLowerBoundary(double value, block_mode_t mode);
};

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_MODEANALOG_HPP
