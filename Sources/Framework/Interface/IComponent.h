#pragma once

<<<<<<< HEAD
#include "IModule.h"
=======
#include "Framework/Interface/IModule.h"
>>>>>>> remotes/origin/Branch_Rebase

namespace ProjectEngine
{
    class Entity;

    class IComponent : public IModule
    {
    public:
        virtual int Initialize() noexcept = 0;
        virtual void Finalize() noexcept = 0;

    public:
        IComponent() : mMaster(nullptr), mIsActive(true) {}

<<<<<<< HEAD
        bool IsActive() { return mIsActive; }
=======
        bool IsActive() const { return mIsActive; }
>>>>>>> remotes/origin/Branch_Rebase
        void SetActive(bool active) { mIsActive = active; }

        Entity* GetMaster() { return mMaster; }
        void SetMaster(Entity* master) { mMaster = master; }

    protected:
        Entity* mMaster;
        bool mIsActive;
    };
}