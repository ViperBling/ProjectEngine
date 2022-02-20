#pragma once

#include "IResource.h"

namespace ProjectEngine
{
    class VertexBuffer : public IVertexBuffer
    {
    public:
        virtual void Initialize(void* data, unsigned int count, VertexFormat vf) noexcept;
        virtual void Finalize() noexcept;
        virtual unsigned int GetVertexSize(VertexFormat vf) noexcept;

    public:
        unsigned int mCount;
        VertexFormat mVertexFormat;
    };
}