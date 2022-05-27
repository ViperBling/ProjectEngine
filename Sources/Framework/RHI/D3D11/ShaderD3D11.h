#pragma once

#include <d3d11.h>

#include "Framework/RHI/Shader.h"

namespace ProjectEngine
{
    class GraphicsManager;

    class ShaderD3D11 : public Shader
    {
    public:
        virtual bool InitializeFromFile(
            GraphicsManager* graphicsManager,
            const std::string& vsPath,
            const std::string& psPath) noexcept;

        virtual void Use(GraphicsManager* gfxManager) noexcept;

        virtual void Finalize(GraphicsManager* gfxManager) noexcept;
        virtual void SetConstantBuffer(GraphicsManager* gfxManager, const ConstantBuffer& cbuffer) noexcept;

    protected:
        ID3D11VertexShader* mVertexShader;
        ID3D11PixelShader* mPixelShader;
        ID3D11InputLayout* mLayout;
        ID3D11Buffer* mMatrixBuffer;
    };
}