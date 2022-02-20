#include "MeshRenderSystem.h"
#include "Object/World.h"
#include "Application/Application.h"
#include "Object/System/MeshRenderSystem.h"

ProjectEngine::MeshRenderSystem::MeshRenderSystem(ProjectEngine::World *world) :
    mWorld(world)
{}

int ProjectEngine::MeshRenderSystem::Initialize() noexcept
{
    mGraphicsManager = mWorld->mApp->mGraphicsManager;
    return 0;
}

void ProjectEngine::MeshRenderSystem::Finalize() noexcept
{
    mMeshes.clear();
}

void ProjectEngine::MeshRenderSystem::Tick() noexcept
{

}

void ProjectEngine::MeshRenderSystem::AddComponent(ProjectEngine::MeshRenderComponent *comp)
{
    mComponents.insert(comp);
}

void ProjectEngine::MeshRenderSystem::DeleteComponent(ProjectEngine::MeshRenderComponent *comp)
{
    mComponents.erase(comp);
}

void ProjectEngine::MeshRenderSystem::Render()
{
    if (!IsActive())
        return;

    for (auto comp : mComponents)
    {
        if (comp->IsVisible())
        {
            auto tranform = comp->GetMaster()->GetComponent<TransformComponent>();

            for (auto mid : comp->mMeshIdx)
            {
                auto mesh = mMeshes[mid];
                if (mesh)
                {
                    mesh->Render(mWorld, tranform->GetWorldMatrix());
                }
            }
        }
    }
}

void ProjectEngine::MeshRenderSystem::LoadMesh(aiMesh *mesh)
{
    auto _mesh = mGraphicsManager->CreateRenderMesh(mesh);
    mMeshes.push_back(_mesh);
}
