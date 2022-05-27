#pragma once

#include "Framework/Interface/IShader.h"

namespace ProjectEngine
{
    class GraphicsManager;

    class Shader : public IShader
    {
    public:
        virtual bool InitializeFromFile(
            GraphicsManager* gfxManager,
            const std::string& vsPath,
            const std::string& psPath) noexcept;

        virtual void Use(GraphicsManager* gfxManager) noexcept;

        virtual void Finalize(GraphicsManager* gfxManager) noexcept;
        virtual void SetConstantBuffer(GraphicsManager* gfxManager, const ConstantBuffer& cbuffer) noexcept;
    };
}