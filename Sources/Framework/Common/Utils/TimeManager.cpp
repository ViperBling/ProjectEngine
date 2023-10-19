#include <iostream>

#include "TimeManager.h"
#include "Framework/Common/Utils/Logging.h"

using namespace ProjectEngine;


int ProjectEngine::TimeManager::Initialize() noexcept {

    PROJECTENGINE_LOG(info) << "Time Manager Initialize OK.";

    mbFirstUpdate = true;
    mStartTime = mLastStatisticTime = std::chrono::high_resolution_clock::now();
    mFrameCount = 0;

    return 0;
}

void ProjectEngine::TimeManager::Finalize() noexcept {

}

void ProjectEngine::TimeManager::Tick(float deltaTime) noexcept {

    auto duration = mFrameStartTime - mLastStatisticTime;
    if (duration > std::chrono::seconds(1)) {
        mFPS = mFrameCount;
        mFrameCount = 0;
        mLastStatisticTime = mFrameStartTime;
        // std::cout << mFPS << std::endl;
    }
    else {
        mFrameCount++;
    }
}

void ProjectEngine::TimeManager::PreTick() noexcept {

    if (mbFirstUpdate) {
        mLastUpdateTime = std::chrono::high_resolution_clock::now();
        mbFirstUpdate = false;
    }

    mFrameStartTime = std::chrono::high_resolution_clock::now();
    auto deltaTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(mFrameStartTime - mLastUpdateTime).count();
    mDeltaTime = (float)deltaTime / 1000.0f;
    mLastUpdateTime = mFrameStartTime;
}

void ProjectEngine::TimeManager::PostTick() noexcept {

    mFrameEndTime = std::chrono::high_resolution_clock::now();
    auto total = mFrameEndTime - mFrameStartTime;
    long long interval = 16666666;
    long long sleep = interval - total.count() - 2000000;

    // if (sleep > 0) {
    //     MicroSleep(sleep);
    // }
}

void ProjectEngine::TimeManager::MicroSleep(unsigned long long int ns) noexcept {
    std::this_thread::sleep_for(std::chrono::nanoseconds(ns));
}
