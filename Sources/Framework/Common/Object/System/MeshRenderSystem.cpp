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
    for (auto mesh : mMeshes) {
        mGraphicsManager->DeleteRenderMesh(mesh);
    }
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

    mGraphicsManager->ClearRenderTarget(0.2f, 0.4f, 0.6f, 1.0f);

    for (auto comp : mComponents)
    {
        if (comp->IsVisible())
        {
            comp->Render();
        }
    }

    mGraphicsManager->Present();
}

void ProjectEngine::MeshRenderSystem::LoadMesh(aiMesh *mesh)
{
    auto _mesh = mGraphicsManager->CreateRenderMesh(mesh);
    mMeshes.push_back(_mesh);
}
