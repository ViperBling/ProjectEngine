#pragma once

#include "IApplication.h"
#include "Framework/Common/Memory/MemoryManager.h"
#include "Framework/RHI/GraphicsManager.h"

namespace ProjectEngine
{
    class Application : public IApplication
    {
    public:
        virtual int Initialize() noexcept;
        virtual void Tick() noexcept;
        virtual void Render() noexcept;
        virtual void Run() noexcept;
        virtual void Finalize() noexcept;
        virtual void Quit() noexcept;
        virtual bool IsQuit() noexcept;

    public:
        MemoryManager* mMemoryManager;
        GraphicsManager* mGraphicsManager;

    private:
        bool mQuit = false;
    };
}