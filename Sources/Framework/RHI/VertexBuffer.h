#pragma once

#include "IResource.h"

namespace ProjectEngine
{
    class VertexBuffer : public IVertexBuffer
    {
    public:
        VertexBuffer(unsigned int count, VertexFormat vertexFormat)
            : mCount(count), mVertexFormat(VertexFormat::None) {}

        virtual size_t GetVertexSize(VertexFormat vertexFormat) noexcept;

    private:
        unsigned int mCount;
        VertexFormat mVertexFormat;
    };
}