#pragma once

#include <d3d11.h>

#include "Framework/RHI/VertexBuffer.h"

namespace ProjectEngine
{
    class GraphicsManager;

    class VertexBufferD3D11 : public VertexBuffer
    {
    public:
        virtual void Initialize(
            GraphicsManager* gfxManager,
            void* data,
            unsigned int count, VertexFormat vf) noexcept;

    public:
        ID3D11Buffer* mVertexBuffer;
    };
}

