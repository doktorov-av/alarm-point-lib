//
// Created by Doktorov Alexander on 6/19/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#include "RbdPointFactory.hpp"
#include "apl/IPointFactory.hpp"
#include "apl/ConfigReader.hpp"
#include "apl/Tracker.hpp"

#include "iostream"
#include "thread"
#include "csignal"

std::atomic<bool> is_running = true;

void sigint_handler(int signum) {
    is_running.store(false);
}

class Handler : public apl::Handler {
    void HandleChange(apl::AlarmPoint *alarmPoint, const apl::AlarmState &changedFrom, const apl::AlarmState &changedTo) override {
        if(auto ptr = changedTo.GetBrokenRule()) {
            std::cout << ptr->GetFailDescription() << '\n';
        } else {
            std::cout << alarmPoint->GetName() << " normalized\n";
        }
    }
};

int main(int argc, char* argv[]) {
    mlbInit(nullptr);
    mlbOpenSPD();

    auto configMap = apl::read_config(std::filesystem::path("./schemas/test_config.json"));
    RbdPointFactory factory{};
    auto points = factory.createPoints(configMap, {});
    Handler handler{};
    apl::Tracker tracker{handler};

    signal(SIGINT, sigint_handler);
    while(is_running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for(auto& pt : points) {
            tracker.Update(pt.get());
        }
    }

    return 0;
}