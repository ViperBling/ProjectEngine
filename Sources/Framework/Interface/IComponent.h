#pragma once

#include "Framework/Interface/IModule.h"

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

        bool IsActive() const { return mIsActive; }
        void SetActive(bool active) { mIsActive = active; }

        Entity* GetMaster() { return mMaster; }
        void SetMaster(Entity* master) { mMaster = master; }

    protected:
        Entity* mMaster;
        bool mIsActive;
    };
}