#pragma once

#include "IShader.h"

namespace ProjectEngine
{
    class Shader : public IShader
    {
    public:

        virtual	bool	InitializeFromFile(const string& vsPath, const string& psPath) noexcept;
        virtual void	Use() noexcept;
        virtual void	Finialize() noexcept;
        virtual void	SetConstantBuffer(const ConstantBuffer& cbuffer) noexcept;
    };
}