#pragma once

#include <d3d11.h>
#include "IndexBuffer.h"

namespace ProjectEngine
{
    class GraphicsManager;

    class IndexBufferD3D11 : public IndexBuffer
    {
    public:
        IndexBufferD3D11(void* data, unsigned int count, IndexFormat iFormat);
        virtual ~IndexBufferD3D11();
        virtual void Initialize(void* data, unsigned int count, IndexFormat iFormat) noexcept;
        virtual void Finalize() noexcept;

    public:
        ID3D11Buffer* mIndexBuffer;
    };
}
