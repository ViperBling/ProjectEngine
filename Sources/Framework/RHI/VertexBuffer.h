#pragma once

#include "Framework/Interface/IResource.h"

namespace ProjectEngine
{
    class VertexBuffer : public IVertexBuffer
    {
    public:
        VertexBuffer(unsigned int count, VertexFormat vf) : mCount(count)
        {
            mVertexFormat = VertexFormat::None;
        }

        virtual size_t GetVertexSize(VertexFormat vf) noexcept;

    private:
        unsigned int mCount;
        VertexFormat mVertexFormat;
    };
}