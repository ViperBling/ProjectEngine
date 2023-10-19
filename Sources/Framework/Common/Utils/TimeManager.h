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
        virtual void Tick(float deltaTime) noexcept;

        void PreTick() noexcept;
        void PostTick() noexcept;

        void MicroSleep(unsigned long long ns) noexcept;

        float GetDeltaTime()const { return mDeltaTime; }

    private:
        bool mbFirstUpdate;

        std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> mLastUpdateTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> mFrameStartTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> mFrameEndTime;

        std::chrono::time_point<std::chrono::high_resolution_clock> mLastStatisticTime;

        int mFrameCount;
        int mFPS;
        float mDeltaTime;   // seconds
    };
}