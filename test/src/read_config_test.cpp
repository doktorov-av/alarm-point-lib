//
// Created by Doktorov Alexander on 6/17/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "ConfigData.hpp"
#include "ConfigReader.hpp"
#include "gtest/gtest.h"

static constexpr auto discreteName = "229RF21P02B2D";
static constexpr auto analogName = "228SG11P01B1D";
static constexpr auto msName = "229RF21P02B2DXXX";

class ConfigTest : public ::testing::Test {
protected:
    void SetUp() override {
        ASSERT_NO_THROW(cfg = apl::read_config(std::filesystem::path("./schemas/test_config.json")));
    }
    std::unordered_map<std::string, apl::ConfigData> cfg;
};

TEST(Config, goodRead) {
    ASSERT_NO_THROW(apl::read_config(std::filesystem::path("./schemas/test_config.json")));
}

TEST(Config, badRead) {
    ASSERT_THROW(apl::read_config(std::filesystem::path("./schemas/test_bad_config.json")), std::exception);
}

TEST_F(ConfigTest, dalarm) {
    ASSERT_FALSE(cfg.at(discreteName).cast<apl::Dalarm>().alarm_state);
}

TEST_F(ConfigTest, dalarmBadAccess) {
    ASSERT_THROW(cfg.at(discreteName).cast<apl::Falarm>().lower_bound, std::bad_variant_access);
}

TEST_F(ConfigTest, falarm) {
    ASSERT_DOUBLE_EQ(cfg.at(analogName).cast<apl::Falarm>().upper_bound, 10);
    ASSERT_DOUBLE_EQ(cfg.at(analogName).cast<apl::Falarm>().lower_bound, -10);
}

TEST_F(ConfigTest, falarmBadAccess) {
    ASSERT_THROW(cfg[analogName].cast<apl::Dalarm>().alarm_state, std::bad_variant_access);
}

TEST_F(ConfigTest, malarm) {
    auto states = cfg.at(msName).cast<apl::MalarmInt>().states;
    ASSERT_EQ(states.size(), 2);
    ASSERT_EQ(states["STATE1"].prohibited, false);
    ASSERT_EQ(states["STATE1"].value, 1);
}

TEST_F(ConfigTest, malarmBadAccess) {
    ASSERT_THROW(cfg.at(msName).cast<apl::Dalarm>().alarm_state, std::bad_variant_access);
}