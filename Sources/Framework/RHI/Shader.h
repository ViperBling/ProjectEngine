#pragma once

#include "Framework/Interface/IShader.h"

namespace ProjectEngine
{

    class Shader : public IShader
    {
    public:
        virtual bool InitializeFromFile(const std::string& vsPath, const std::string& psPath) noexcept;
        virtual void Use() noexcept;
        virtual void Finalize() noexcept;
        virtual void SetConstantBuffer(const ConstantBuffer& cbuffer) noexcept;
    };
}