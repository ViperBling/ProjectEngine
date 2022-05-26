#pragma once

<<<<<<< HEAD
#include "IModule.h"
=======
#include "Framework/Interface/IModule.h"
>>>>>>> remotes/origin/Branch_Rebase

namespace ProjectEngine
{
    class ISystem : public IModule
    {
    public:
        virtual int Initialize() noexcept = 0;
        virtual void Finalize() noexcept = 0;

    public:
        virtual bool IsActive() { return mIsActive; }
        virtual void Activate() { mIsActive = true; }
        virtual void Deactivate() { mIsActive = false; }

    private:
        bool mIsActive;
    };

    class ITickableSystem : public ISystem
    {
    public:
        virtual int Initialize() noexcept = 0;
        virtual void Finalize() noexcept = 0;
        virtual void Tick() noexcept = 0;
    };
}