#pragma once

#include <memory>

#include "Framework/Common/Object/Entity.h"
#include "Framework/Interface/ISystem.h"

namespace ProjectEngine
{
    class World;

    class CameraSystem : public ITickableSystem
    {
    public:

        CameraSystem(World* world);
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void Tick() noexcept;

        std::shared_ptr<Entity> GetMainCamera();
        void SetMainCamera(std::shared_ptr<Entity> camera);

    private:

        World* mWorld;
        std::shared_ptr<Entity> mMainCamera;
    };
}