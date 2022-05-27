#pragma once

#include "Framework/Interface/IResource.h"

namespace ProjectEngine
{

    class VertexBuffer : public IVertexBuffer
    {
    public:
        virtual void Initialize(void* data, unsigned int count, VertexFormat vf) noexcept;
        virtual unsigned int GetVertexSize(VertexFormat vf) noexcept;
        virtual void Finalize() noexcept;

        unsigned int GetCount() { return mCount; }
        VertexFormat GetVertexFormat() { return mVertexFormat; }

    private:
        unsigned int mCount;
        VertexFormat mVertexFormat;
    };
}