#pragma once

#include "Framework/Interface/IResource.h"

namespace ProjectEngine
{

    class IndexBuffer : public IIndexBuffer
    {
    public:
        virtual void Initialize(void* data, unsigned int count, IndexFormat iFormat) noexcept;
        virtual void Finalize() noexcept;

        unsigned int GetCount() { return mCount; }
        IndexFormat GetIndexBufferFormat() { return mIndexFormat; }

    private:
        unsigned int mCount;
        IndexFormat mIndexFormat;
    };
}