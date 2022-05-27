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

    for (auto comp : mMeshRenderComps) {
        if (comp->IsVisible()) {

            auto transform = comp->GetMaster()->GetComponent<TransformComponent>();
            auto position = transform->GetPosition();
            auto scale = transform->GetScale();
            auto rotation = transform->GetRotation();
            auto translation = BuildTranslationMatrix(position);
            auto scaling = BuildScaleMatrix(scale);
            auto rx = BuildRotationMatrix(Vector3f(1, 0, 0), rotation.x());
            auto ry = BuildRotationMatrix(Vector3f(0, 1, 0), rotation.y());
            auto rz = BuildRotationMatrix(Vector3f(0, 0, 1), rotation.z());

            auto worldMatrix = translation * rz * ry * rx * scaling; // make sure translation matrix go first.

            for (auto mId : comp->mMeshIdx) {
                auto mesh = mMeshes[mId];
                if (mesh) {
                    mesh->Render(mGraphicsManager, mWorld, worldMatrix);
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

