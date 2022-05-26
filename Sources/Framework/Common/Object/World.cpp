#include "World.h"
#include "Platform/Assert.h"

#include "Framework/Common/Object/Components/MeshRenderComponent.h"

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <iostream>

using namespace ProjectEngine;
using namespace std;

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

    if (!mEntities[guid]) return nullptr;
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

void ProjectEngine::World::LoadScene(const std::string& scenePath) {

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        scenePath,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    PROJECTENGINE_ASSERT(scene);

    for (unsigned int i = 0; i < scene->mRootNode->mNumChildren; ++i) {
        auto child = scene->mRootNode->mChildren[i];
        if (child->mNumMeshes <= 0) continue;

        auto entity = CreateEntity();
        auto meshRenderComp = entity->AddComponent<MeshRenderComponent>();

        for (unsigned int j = 0; j < child->mNumMeshes; ++j) {
            auto mIdx = child->mMeshes[j];
            auto mesh = scene->mMeshes[mIdx];
            auto robj = meshRenderComp->AddRenderObject();
            robj->SetName(mesh->mName.C_Str());
        }
    }
}

void World::DumpEntities() {

    cout << "Dump Entities: " << endl;

    for (auto& pair : mEntities) {
        auto guid = pair.first;
        auto entity = pair.second;

        cout << "Guid: " << guid << endl;
        cout << "Transform Component: " << endl;
        auto position = entity->GetComponent<TransformComponent>()->GetPosition();
        cout << "position: (" << position.x() << ", " << position.y() << ", " << position.z() << ")" << endl;

        auto meshRender = entity->GetComponent<MeshRenderComponent>();
        if (meshRender) {
            cout << "MeshRenderComponent: " << endl;
            for (int i = 0; i < meshRender->GetRenderObjectCount(); ++i) {
                auto robj = meshRender->GetRenderObject(i);
                cout << "RenderObject: " << robj->GetName() << endl;
            }
        }
        cout << endl;
    }
}
