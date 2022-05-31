#pragma once

#include "Framework/RHI/Material.h"

namespace ProjectEngine
{
    class MaterialD3D11 : public Material
    {
    public:
        virtual void Apply(ConstantBuffer cb) noexcept;
    };
}