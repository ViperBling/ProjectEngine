#pragma once

#include "Framework/Interface/IResource.h"

namespace ProjectEngine
{
    class SamplerState : public ISamplerState
    {
    public:
        virtual void Initialize() noexcept;
        virtual void Finalize() noexcept;
    };
}