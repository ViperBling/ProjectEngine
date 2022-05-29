#pragma once

#include "Framework/Interface/IModule.h"

namespace ProjectEngine
{
    class IOManager : public IModule
    {
    public:
        virtual int Initialize() noexcept = 0;
        virtual void Finalize() noexcept = 0;
    };
}