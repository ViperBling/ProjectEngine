#pragma once

#include "Allocator.h"
#include "IModule.h"
#include "Singleton.h"

namespace ProjectEngine
{
    class MemoryManager : public IModule
    {
    public:
        template<class T, typename... Arguments>
        T* New(Arguments... parameters)
        {
            return new (Allocate(sizeof(T))) T(parameters...);
        }

        template<class T>
        void Delete(T* p)
        {
            p->~T();
            Free(p, sizeof(T));
        }

    public:
        MemoryManager() = default;
        virtual ~MemoryManager() = default;

        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;

        void* Allocate(size_t size);
        void  Free(void* p, size_t size);

    private:
        static size_t*        m_pBlockSizeLookup;
        static Allocator*     m_pAllocators;

    private:
         MemoryManager(const MemoryManager& manager) = default;
         MemoryManager& operator=(const MemoryManager&) = default;

        static Allocator* LookUpAllocator(size_t size);
    };
}