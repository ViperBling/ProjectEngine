#pragma once

#include <d3d11.h>

#include "Framework/RHI/IndexBuffer.h"

namespace ProjectEngine
{
    class GraphicsManager;

    class IndexBufferD3D11 : public IndexBuffer
    {
    public:

        virtual void Initialize(GraphicsManager* gfxManager, void* data, unsigned int count, IndexFormat iFormat) noexcept;

        ID3D11Buffer* GetIndexBuffer() { return mIndexBuffer; }
        void ReleaseBuffer() { mIndexBuffer->Release(); mIndexBuffer = nullptr; }

    private:
        ID3D11Buffer* mIndexBuffer;
    };
}