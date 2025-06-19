//
// Created by Doktorov Alexander on 6/17/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "ConfigReader.hpp"
#include "gtest/gtest.h"

TEST(Config, goodRead) {
    ASSERT_NO_THROW(apl::read_config("./schemas/test_config.json", "./schemas/config.schema.json"));
}

TEST(Config, badRead) {
    ASSERT_THROW(apl::read_config("./schemas/test_bad_config.json", "./schemas/config.schema.json"), std::exception);
}