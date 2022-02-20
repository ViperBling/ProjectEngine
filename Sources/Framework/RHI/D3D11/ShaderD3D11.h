#pragma once

#include <d3d11.h>
#include "Shader.h"

namespace ProjectEngine
{
    class ShaderD3D11 : public Shader
    {
    public:

        ShaderD3D11(const string& vsPath, const string& psPath);
        virtual ~ShaderD3D11();

        virtual	bool	InitializeFromFile(const string& vsPath, const string& psPath) noexcept;
        virtual	void	Use() noexcept;
        virtual void	Finalize() noexcept;
        virtual void	SetConstantBuffer(const ConstantBuffer& cbuffer) noexcept;

    public:
        ID3D11VertexShader*		m_vertexShader;
        ID3D11PixelShader*		m_pixelShader;
        ID3D11InputLayout*		m_layout;
        ID3D11Buffer*			m_matrixBuffer;
    };
}