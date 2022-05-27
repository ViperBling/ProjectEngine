#pragma once

#include <string>
#include <DirectXMath.h>

#include "Framework/Common/Math/MathLib.h"

using namespace DirectX;

namespace ProjectEngine
{
    class GraphicsManager;

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
            GraphicsManager* graphicsManager,
            const std::string& vsPath,
            const std::string& psPath) noexcept = 0;

        virtual void Use(GraphicsManager* graphicsManager) noexcept = 0;

        virtual void Finalize(GraphicsManager* graphicsManager) noexcept = 0;
        virtual void SetConstantBuffer(GraphicsManager* graphicsManager, const ConstantBuffer& cbuffer) noexcept = 0;
    };
}