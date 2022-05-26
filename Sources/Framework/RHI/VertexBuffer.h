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

        virtual size_t GetVertexSize(VertexFormat vf) noexcept;

    private:
        unsigned int mCount;
        VertexFormat mVertexFormat;
    };
}