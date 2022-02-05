#include "MemoryManager.hpp"
#include <malloc.h>

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
    static const uint32_t kNumBlockSizes = sizeof(kBlockSizes) / sizeof(kBlockSizes[0]);

    // 最大可用块，也就是上面数组中的1024
    static const uint32_t kMaxBlockSize = kBlockSizes[kNumBlockSizes - 1];
}

int MemoryManager::Initialize()
{
    // 只初始化一次
    static bool s_bInitialized = false;
    if (!s_bInitialized)
    {
        // 初始化块大小查找表，根据索引快速查找到要用的块
        m_pBlockSizeLookup = new size_t[kMaxBlockSize + 1];
        size_t j = 0;
        for (size_t i = 0; i <= kMaxBlockSize; i++)
        {
            if (i > kBlockSizes[j]) ++j;
            m_pBlockSizeLookup[i] = j;
        }

        // Initialize the allocators
        m_pAllocators = new Allocator[kNumBlockSizes];
        for (size_t i = 0; i < kNumBlockSizes; i++)
        {
            m_pAllocators[i].Reset(kBlockSizes[i], kPageSize, kAlignment);
        }
    }
    return 0;
}

void MemoryManager::Finalize()
{
    delete[] m_pAllocators;
    delete[] m_pBlockSizeLookup;
}

void MemoryManager::Tick()
{
    
}

Allocator* MemoryManager::LookUpAllocator(size_t size)
{
    // check eligibility for lookup
    if (size <= kMaxBlockSize)
        return m_pAllocators + m_pBlockSizeLookup[size];
    else
        return nullptr;
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




