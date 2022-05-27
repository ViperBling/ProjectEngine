#include "IndexBuffer.h"

using namespace ProjectEngine;

void IndexBuffer::Initialize(void* data, unsigned int count, IndexFormat iFormat) noexcept
{
    mCount = count;
    mIndexFormat = iFormat;
}

void IndexBuffer::Finalize() noexcept {

}
