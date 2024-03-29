#pragma once

#include "IApplication.h"
#include "Framework/Common/IO/Keyboard.h"
#include "Framework/Common/IO/Mouse.h"
#include "Framework/RHI/GraphicsManager.h"
#include "Framework/Common/Object/World.h"
#include "Framework/Common/Utils/TimeManager.h"
#include "Framework/Common/Memory/MemoryManager.h"
#include "Framework/Common/Object/System/CameraSystem.h"

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

        void SetSize(int width, int height) noexcept;

    public:
        MemoryManager* mMemoryManager{};
        GraphicsManager* mGraphicsManager{};
        TimeManager* mTimeManager{};
        World* mWorld{};

        KeyboardManager* mKbdManager{};
        MouseManager* mMouseManager{};

        int width{1280};
        int height{720};

    private:
        bool mQuit = false;
    };

    extern Application* GApp;
}