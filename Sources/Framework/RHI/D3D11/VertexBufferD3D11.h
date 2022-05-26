#pragma once

#include <d3d11.h>

#include "Framework/RHI/VertexBuffer.h"

namespace ProjectEngine
{
    class VertexBufferD3D11 : public VertexBuffer
    {
    public:
        VertexBufferD3D11(unsigned int count, VertexFormat vf);

    public:
        ID3D11Buffer* mVertexBuffer;
    };
}

