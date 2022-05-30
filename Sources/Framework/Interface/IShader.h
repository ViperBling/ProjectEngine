#pragma once

#include <string>
#include <DirectXMath.h>

#include "Framework/Common/Math/MathLib.h"
#include "Framework/Interface/IResource.h"

using namespace DirectX;

namespace ProjectEngine
{
    class IShader
    {
    public:
        virtual bool InitializeFromFile(
            const std::string& vsPath,
            const std::string& psPath) noexcept = 0;

        virtual void Use() noexcept = 0;

        virtual void Finalize() noexcept = 0;
        virtual void SetConstantBuffer(const ConstantBuffer& cbuffer) noexcept = 0;
    };
}