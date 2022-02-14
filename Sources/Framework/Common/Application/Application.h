#pragma once

#include "IApplication.h"
#include "Memory/MemoryManager.h"
#include "GraphicsManager.h"
#include "Object/World.h"

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