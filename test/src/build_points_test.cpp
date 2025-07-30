//
// Created by Doktorov Alexander on 6/24/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "gtest/gtest.h"
#include "ConfigReader.hpp"
#include "TestAnalogPoint.hpp"
#include "TestBooleanPoint.hpp"

TEST(BuildPoints, success) {
    auto cfg = apl::read_config(std::filesystem::path("./schemas/test_config.json"));
}