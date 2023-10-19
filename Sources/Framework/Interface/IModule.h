#pragma once

#include "Platform/Assert.h"

namespace ProjectEngine
{
    class IModule
    {
    public:
        virtual int Initialize() noexcept = 0;
        virtual void Finalize() noexcept = 0;
    };

    class ITickableModule : public IModule
    {
        virtual void Tick(float deltaTime) noexcept = 0;
    };
}