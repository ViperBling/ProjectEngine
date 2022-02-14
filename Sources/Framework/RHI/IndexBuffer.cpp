#include "IndexBuffer.h"

using namespace ProjectEngine;

void IndexBuffer::Initialize(void * data, unsigned int count, IndexFormat iformat) noexcept
{
    mCount = count;
    mIndexFormat = iformat;
}

void IndexBuffer::Finialize() noexcept
{
}