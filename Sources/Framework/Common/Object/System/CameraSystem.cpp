#include "CameraSystem.h"

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

    mMainCamera = camera;
}
