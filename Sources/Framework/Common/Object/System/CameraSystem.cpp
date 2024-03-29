#include "CameraSystem.h"

#include <utility>

using namespace ProjectEngine;

CameraSystem::CameraSystem(World *world) :
    mWorld(world)
{

}

int CameraSystem::Initialize() noexcept {

    return 0;
}

void CameraSystem::Finalize() noexcept {

    mMainCamera = nullptr;
}

std::shared_ptr<Entity> CameraSystem::GetMainCamera() {

    return mMainCamera;
}

void CameraSystem::SetMainCamera(std::shared_ptr<Entity> camera) {

    mMainCamera = std::move(camera);
}

void CameraSystem::Tick(float deltaTime) noexcept {

    auto camera = mMainCamera->GetComponent<CameraComponent>();
    camera->Update(deltaTime);
}

void ProjectEngine::CameraSystem::UpdateCamera(MouseManager* mouseManager, KeyboardManager* keyboardManager, float deltaTime)
{

}
