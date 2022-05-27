#pragma once

#include <d3d11.h>

#include "Framework/RHI/VertexBuffer.h"

namespace ProjectEngine
{

    class VertexBufferD3D11 : public VertexBuffer
    {
    public:
        VertexBufferD3D11(void* data, unsigned int count, VertexFormat vf) noexcept;
        virtual ~VertexBufferD3D11();
        virtual void Initialize(void* data, unsigned int count, VertexFormat vf) noexcept;
        virtual void Finalize() noexcept;

    public:
        ID3D11Buffer* mVertexBuffer;
    };
}

