#include "VertexBuffer.h"

using namespace ProjectEngine;

size_t VertexBuffer::GetVertexSize(VertexFormat vertexFormat) noexcept
{
    if (vertexFormat == VertexFormat::VF_N3F || vertexFormat == VertexFormat::VF_P3F)
    {
        return sizeof(float) * 3;
    }
    else if (vertexFormat == VertexFormat::VF_C4B)
    {
        return 4;
    }
    else if (vertexFormat == VertexFormat::VF_T2F) {
        return sizeof(float) * 2;
    }
    else {
        return 0;
    }
}