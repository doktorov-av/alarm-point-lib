//
// Created by Doktorov Alexander on 6/17/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "ConfigReader.hpp"
#include "gtest/gtest.h"

TEST(Config, read) {
    const auto data = apl::read_config("./schemas/test_config.json");
    ASSERT_EQ(data.size(), 3);
    for(auto& point : data) {
        std::cout << point.name << '\n';
        std::cout << point.TypeString() << '\n';
    }
}
