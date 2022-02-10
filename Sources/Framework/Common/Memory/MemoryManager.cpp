#include <iostream>
#include "MemoryManager.h"

extern "C" void* malloc(size_t size);
extern "C" void  free(void* p);

using namespace ProjectEngine;

namespace ProjectEngine
{
    static const uint32_t kBlockSizes[] = {
        // 4倍
        4,  8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
        52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96,

        // 32倍
        128, 160, 192, 224, 256, 288, 320, 352, 384,
        416, 448, 480, 512, 544, 576, 608, 640,

        // 64倍
        704, 768, 832, 896, 960, 1024
    };

    static const uint32_t kPageSize  = 8192;
    static const uint32_t kAlignment = 4;

    // number of elements in the block size array
    static const uint32_t kNumBlockSizes =
            sizeof(kBlockSizes) / sizeof(kBlockSizes[0]);

    // 最大可用块，也就是上面数组中的1024
    static const uint32_t kMaxBlockSize =
            kBlockSizes[kNumBlockSizes - 1];

    size_t*        MemoryManager::m_pBlockSizeLookup;
    Allocator*     MemoryManager::m_pAllocators;
}

int MemoryManager::Initialize() noexcept
{
    static bool s_bInitialized = false;
    if (!s_bInitialized)
    {
        m_pBlockSizeLookup = new size_t[kMaxBlockSize + 1];
        size_t j = 0;
        for (size_t i = 0; i <= kMaxBlockSize; ++i)
        {
            if (i > kBlockSizes[j]) ++j;
            m_pBlockSizeLookup[i] = j;
        }

        m_pAllocators = new Allocator[kNumBlockSizes];
        for (size_t i = 0; i < kNumBlockSizes; ++i)
        {
            m_pAllocators[i].Reset(kBlockSizes[i], kPageSize, kAlignment);
        }

        s_bInitialized = true;
    }
    return 0;
}

void MemoryManager::Finalize() noexcept
{
    delete[] m_pBlockSizeLookup;
    delete[] m_pAllocators;
}

Allocator* MemoryManager::LookUpAllocator(size_t size)
{
    if (size <= kMaxBlockSize) {
        return m_pAllocators + m_pBlockSizeLookup[size];
    }
    else {
        return nullptr;
    }
}

void* MemoryManager::Allocate(size_t size)
{
    Allocator* pAlloc = LookUpAllocator(size);
    if (pAlloc)
        return pAlloc->Allocate();
    else
        return malloc(size);
}

void MemoryManager::Free(void* p, size_t size)
{
    Allocator* pAlloc = LookUpAllocator(size);
    if (pAlloc)
        pAlloc->Free(p);
    else
        free(p);
}