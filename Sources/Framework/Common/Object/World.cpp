//
// Created by qiuso on 2022/5/26.
//

#include "World.h"

using namespace ProjectEngine;

int ProjectEngine::World::Initialize() noexcept {
    mMeshRenderSystem = new MeshRenderSystem();
    mMeshRenderSystem->Initialize();

    return 0;
}

void ProjectEngine::World::Finalize() noexcept {
    mEntities.clear();
}

void ProjectEngine::World::Tick() noexcept {
    mMeshRenderSystem->Tick();
}

void ProjectEngine::World::Render() noexcept {
    mMeshRenderSystem->Render();
}

ProjectEngine::World::World() :
    mMeshRenderSystem(nullptr)
{

}

std::shared_ptr<ProjectEngine::Entity> ProjectEngine::World::CreateEntity() {

    auto entity = std::make_shared<Entity>();
    entity->Initialize(this);
    mEntities[entity->GetGuid()] = entity;
    return entity;
}

std::shared_ptr<ProjectEngine::Entity> ProjectEngine::World::CreateEntity(const xg::Guid &guid) {

    if (mEntities[guid]) return nullptr;

    auto entity = std::make_shared<Entity>(guid);
    entity->Initialize(this);
    mEntities[guid] = entity;

    return entity;
}

std::shared_ptr<ProjectEngine::Entity> ProjectEngine::World::GetEntity(const xg::Guid &guid) {

    return mEntities[guid];
}

void ProjectEngine::World::DeleteEntity(const xg::Guid &guid) {

    auto entity = mEntities[guid];
    if (entity) {
        entity->Finalize();
        mEntities.erase(guid);
    }
}

size_t ProjectEngine::World::GetEntityCount() {
    return mEntities.size();
}

void ProjectEngine::World::LoadScene(std::string scenePath) {

    auto entity = CreateEntity();
    entity->AddComponent<MeshRenderComponent>();

    auto mesh = entity->GetComponent<MeshRenderComponent>();
    mesh->SetVisible(true);
    mesh->AddRenderObject("aili");
}
