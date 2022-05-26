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

    for (auto mesh : mMeshes) {
        mGraphicsManager->DeleteRenderMesh(mesh);
    }
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

    mGraphicsManager->ClearRenderTarget(0.2f, 0.2f, 0.2f, 1.0f);

    for (auto comp : mMeshRenderComps) {
        if (comp->IsVisible()) {
            comp->Render();
        }
    }

    mGraphicsManager->Present();
}

void ProjectEngine::MeshRenderSystem::LoadMesh(aiMesh *mesh) {
    auto _mesh = mGraphicsManager->CreateRenderMesh(mesh);
    mMeshes.emplace_back(_mesh);
}

