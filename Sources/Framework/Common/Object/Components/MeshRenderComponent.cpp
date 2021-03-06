#include "MeshRenderComponent.h"
#include "Framework/Common/Object/Entity.h"
#include "Framework/Common/Object/World.h"

using namespace ProjectEngine;

int ProjectEngine::MeshRenderComponent::Initialize() noexcept {

    auto master = GetMaster();
    if (master) {
        auto world = master->GetWorld();
        if (world) {
            world->GetMeshRenderSystem()->AddComponent(this);
        }
    }

    return 0;
}

void ProjectEngine::MeshRenderComponent::Finalize() noexcept {

    auto master = GetMaster();
    if (master) {
        auto world = master->GetWorld();
        if (world) {
            world->GetMeshRenderSystem()->DeleteComponent(this);
        }
    }
}