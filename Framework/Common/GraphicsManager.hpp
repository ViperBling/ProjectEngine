#pragma once

#include "IRuntimeModule.hpp"

namespace ProjectEngine
{
    class GraphicsManager : implements IRuntimeModule
    {
    public:
        virtual ~GraphicsManager() {}

        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();
    };
} // namespace ProjectEngine
