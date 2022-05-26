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

void ProjectEngine::MeshRenderComponent::Render() {
    for (auto mesh : mRenderObjects) {
        if (mesh->IsVisible()) {
            mesh->Render();
        }
    }
}

std::shared_ptr<RenderObject> ProjectEngine::MeshRenderComponent::AddRenderObject() {

    auto renderObject = std::make_shared<RenderObject>();
    renderObject->SetVisible(true);
    mRenderObjects.emplace_back(renderObject);

    return renderObject;
}

shared_ptr<RenderObject> ProjectEngine::MeshRenderComponent::GetRenderObject(int idx) {

    return mRenderObjects[idx];
}

size_t ProjectEngine::MeshRenderComponent::GetRenderObjectCount() {
    return mRenderObjects.size();
}



