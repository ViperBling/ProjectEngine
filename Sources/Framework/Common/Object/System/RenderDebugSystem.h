#pragma once

#include "Framework/Interface/ISystem.h"

namespace ProjectEngine
{
    class World;

    class RenderDebugSystem : ISystem
    {
    public:

        RenderDebugSystem(World* world);
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;

    private:
        World* mWorld;
    };
}