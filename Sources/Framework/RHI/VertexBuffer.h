#pragma once

#include "Framework/Interface/IResource.h"

namespace ProjectEngine
{
    class GraphicsManager;

    class VertexBuffer : public IVertexBuffer
    {
    public:
        virtual void Initialize(
            GraphicsManager* graphicsManager,
            void* data,
            unsigned int count, VertexFormat vf) noexcept;

        virtual unsigned int GetVertexSize(VertexFormat vf) noexcept;

        unsigned int GetCount() { return mCount; }
        VertexFormat GetVertexFormat() { return mVertexFormat; }

    private:
        unsigned int mCount;
        VertexFormat mVertexFormat;
    };
}