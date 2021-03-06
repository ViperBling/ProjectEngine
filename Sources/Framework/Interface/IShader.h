#pragma once

#include <string>
#include <DirectXMath.h>

#include "Framework/Common/Math/MathLib.h"

using namespace DirectX;

namespace ProjectEngine
{
    struct ConstantBuffer
    {
        Matrix4f world;
        Matrix4f view;
        Matrix4f projection;
    };

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