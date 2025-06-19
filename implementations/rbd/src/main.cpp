//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "RbdPointFactory.hpp"
#include "apl/AlarmPointRepo.hpp"
#include "apl/ConfigReader.hpp"


int main(int argc, char* argv[]) {
    mlbInit(nullptr);
    mlbOpenSPD();

    RbdPointFactory factory{};
    apl::AlarmPointRepo repo(factory);
    auto configs = apl::read_config(std::filesystem::path("./schemas/test_config.json"));
    repo.Load(configs);
    return 0;
}