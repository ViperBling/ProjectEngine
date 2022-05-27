#pragma once

#include <d3d11.h>

#include "Framework/RHI/Shader.h"

namespace ProjectEngine
{
    class GraphicsManager;

    class ShaderD3D11 : public Shader
    {
    public:
        ShaderD3D11(const std::string& vsPath, const std::string& psPath);
        virtual ~ShaderD3D11();

        virtual bool InitializeFromFile(const std::string& vsPath, const std::string& psPath) noexcept;
        virtual void Use() noexcept;

        virtual void Finalize() noexcept;
        virtual void SetConstantBuffer(const ConstantBuffer& cbuffer) noexcept;

    protected:
        ID3D11VertexShader* mVertexShader;
        ID3D11PixelShader* mPixelShader;
        ID3D11InputLayout* mLayout;
        ID3D11Buffer* mMatrixBuffer;
    };
}