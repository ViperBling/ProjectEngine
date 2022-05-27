#include "IndexBuffer.h"


void ProjectEngine::IndexBuffer::Initialize(
    ProjectEngine::GraphicsManager *gfxManager,
    void *data, unsigned int count,
    ProjectEngine::IndexFormat iFormat) noexcept
{
    mCount = count;
    mIndexFormat = iFormat;
}
