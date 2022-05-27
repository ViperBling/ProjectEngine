#include "MeshRenderSystem.h"
#include "Framework/Common/Object/World.h"
#include "Framework/Common/Application/Application.h"


ProjectEngine::MeshRenderSystem::MeshRenderSystem(ProjectEngine::World *world) :
    mWorld(world)
{

}


int ProjectEngine::MeshRenderSystem::Initialize() noexcept {

    mGraphicsManager = mWorld->mApp->mGraphicsManager;
    return 0;
}

void ProjectEngine::MeshRenderSystem::Finalize() noexcept {

    mMeshes.clear();
}

void ProjectEngine::MeshRenderSystem::Tick() noexcept {

}

void ProjectEngine::MeshRenderSystem::AddComponent(ProjectEngine::MeshRenderComponent *meshRenderComp) {

    mMeshRenderComps.insert(meshRenderComp);
}

void ProjectEngine::MeshRenderSystem::DeleteComponent(ProjectEngine::MeshRenderComponent *meshRenderComp) {

    mMeshRenderComps.erase(meshRenderComp);
}

void ProjectEngine::MeshRenderSystem::Render() {

    if (!IsActive()) return;

    for (auto comp : mMeshRenderComps) {
        if (comp->IsVisible()) {

            auto transform = comp->GetMaster()->GetComponent<TransformComponent>();

            for (auto mId : comp->mMeshIdx) {
                auto mesh = mMeshes[mId];
                if (mesh) {
                    mesh->Render(mWorld, transform->GetWorldMatrix());
                }
            }
        }
    }

    mGraphicsManager->Present();
}

void ProjectEngine::MeshRenderSystem::LoadMesh(aiMesh *mesh) {

    auto _mesh = mGraphicsManager->CreateRenderMesh(mesh);
    mMeshes.emplace_back(_mesh);
}

