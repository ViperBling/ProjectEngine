#pragma once

#include <string>
#include "Math/MathLib.h"
#include <DirectXMath.h>

using namespace DirectX;
using namespace std;

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

        virtual bool InitializeFromFile(const string& vsPath, const string& psPath) noexcept = 0;
        virtual void Use() noexcept = 0;
        virtual void Finalize() noexcept = 0;
        virtual void SetConstantBuffer(const ConstantBuffer& cbuffer) noexcept = 0;
    };
}