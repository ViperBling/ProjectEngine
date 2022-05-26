#include "MeshRenderComponent.h"
<<<<<<< HEAD
#include "Object/Entity.h"
#include "Object/World.h"

using namespace ProjectEngine;

int MeshRenderComponent::Initialize() noexcept
{
    auto master = GetMaster();
    if (master)
    {
        auto world = master->GetWorld();
        if (world)
        {
            world->GetMeshRenderSystem()->AddComponent(this);
        }
    }
    return 0;
}

void MeshRenderComponent::Finalize() noexcept
{
    auto master = GetMaster();
    if (master)
    {
        auto world = master->GetWorld();
        if (world)
        {
            world->GetMeshRenderSystem()->DeleteComponent(this);
        }
    }
}
=======
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
>>>>>>> remotes/origin/Branch_Rebase
