#pragma once

#include <memory>

#include "Framework/Common/Object/Entity.h"
#include "Framework/Interface/ISystem.h"
#include "Framework/Common/IO/Mouse.h"
#include "Framework/Common/IO/Keyboard.h"

namespace ProjectEngine
{
    class World;

    class CameraSystem : public ITickableSystem
    {
    public:

        CameraSystem(World* world);
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void Tick(float deltaTime) noexcept;

        void UpdateCamera(MouseManager* mouseManager, KeyboardManager* keyboardManager, float deltaTime);

        std::shared_ptr<Entity> GetMainCamera();
        void SetMainCamera(std::shared_ptr<Entity> camera);

    private:

        World* mWorld;
        std::shared_ptr<Entity> mMainCamera;
    };
}