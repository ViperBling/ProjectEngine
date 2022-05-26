//
// Created by qiuso on 2022/5/26.
//

#include "MeshRenderSystem.h"

int ProjectEngine::MeshRenderSystem::Initialize() noexcept {
    return 0;
}

void ProjectEngine::MeshRenderSystem::Finalize() noexcept {

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
            comp->Render();
        }
    }
}
