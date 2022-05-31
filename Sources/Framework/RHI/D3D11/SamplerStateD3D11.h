#pragma once

#include <d3d11.h>

#include "Framework/RHI/SamplerState.h"

namespace ProjectEngine
{
    class SamplerStateD3D11 : public SamplerState
    {
    public:
        SamplerStateD3D11();
        virtual ~SamplerStateD3D11();

        virtual void Initialize() noexcept;
        virtual void Finalize() noexcept;

    public:
        ID3D11SamplerState* mSampler;
    };
}