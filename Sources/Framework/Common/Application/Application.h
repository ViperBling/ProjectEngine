#pragma once

#include "IApplication.h"
<<<<<<< HEAD
#include "Memory/MemoryManager.h"
#include "GraphicsManager.h"
#include "Object/World.h"
=======
#include "Framework/Common/Memory/MemoryManager.h"
#include "Framework/RHI/GraphicsManager.h"
#include "Framework/Common/Object/World.h"
>>>>>>> remotes/origin/Branch_Rebase

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

        World* mWorld;

    private:
        bool mQuit = false;
    };

    extern Application* GApp;
}