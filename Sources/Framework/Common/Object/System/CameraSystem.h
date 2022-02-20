#pragma once

#include <memory>
#include "Object/Entity.h"
#include "ISystem.h"

namespace ProjectEngine
{
    class World;

    class CameraSystem : public IModule
    {
    public:
        CameraSystem(World* world);
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;

    public:
        std::shared_ptr<Entity> GetMainCamera();
        void SetMainCamera(std::shared_ptr<Entity> camera);

    private:
        World* mWorld;
        std::shared_ptr<Entity> mMainCamera;
    };
}