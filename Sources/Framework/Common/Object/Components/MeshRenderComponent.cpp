#include "MeshRenderComponent.h"
#include "Framework/Common/Object/Entity.h"
#include "Framework/Common/Object/World.h"


int ProjectEngine::MeshRenderComponent::Initialize() noexcept {
    GetMaster()->GetWorld()->GetMeshRenderSystem()->AddComponent(this);
    return 0;
}

void ProjectEngine::MeshRenderComponent::Finalize() noexcept {
    GetMaster()->GetWorld()->GetMeshRenderSystem()->DeleteComponent(this);
}

void ProjectEngine::MeshRenderComponent::Render() {
    for (auto mesh : mRenderObjects) {
        if (mesh->IsVisible()) {
            mesh->Render();
        }
    }
}

void ProjectEngine::MeshRenderComponent::AddRenderObject(std::string resourePath) {
    auto renderObject = std::make_shared<RenderObject>();
    renderObject->SetVisible(true);
    mRenderObjects.emplace_back(renderObject);
}
