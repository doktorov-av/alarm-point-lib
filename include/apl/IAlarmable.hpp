//
// Created by DoktorovAlexander on 25.05.2025.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef IALARMABLE_HPP
#define IALARMABLE_HPP

class IAlarmable {
public:
    virtual ~IAlarmable() = default;
    [[nodiscard]] virtual bool InAlarm() const = 0;
};

#endif //IALARMABLE_HPP
