#pragma once

#include <thread>
#include <chrono>
#include "Framework/Interface/IModule.h"

namespace ProjectEngine
{
    class TimeManager : public ITickableModule
    {
    public:
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void Tick() noexcept;

        void PreTick() noexcept;
        void PostTick() noexcept;

        void MicroSleep(unsigned long long ns) noexcept;

    private:
        bool mbFirstUpdate;

        std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> mLastUpdateTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> mFrameStartTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> mFrameEndTime;

        std::chrono::time_point<std::chrono::high_resolution_clock> mLastStatisticTime;

        int mFrameCount;
        int mFPS;
        std::chrono::nanoseconds mDeltaTime;
    };
}