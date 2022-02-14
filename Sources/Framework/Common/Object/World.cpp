#include <iostream>

#include "Platform/Assert.h"
#include "World.h"
#include "Components/MeshRenderComponent.h"

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

using namespace std;
using namespace ProjectEngine;

World::World(Application *app) : mApp(app), mMeshRenderSystem(nullptr)
{}

int World::Initialize() noexcept
{
    mMeshRenderSystem = new MeshRenderSystem(this);
    mMeshRenderSystem->Initialize();

    return 0;
}

void World::Finalize() noexcept
{
    mEntities.clear();
    mMeshRenderSystem->Finalize();
}

void World::Tick() noexcept
{
    mMeshRenderSystem->Tick();
}

void World::Render() noexcept
{
    mMeshRenderSystem->Render();
}

std::shared_ptr<Entity> World::CreateEntity()
{
    auto entity = std::make_shared<Entity>();
    entity->Initialize(this);
    mEntities[entity->GetGuid()] = entity;
    return entity;
}

std::shared_ptr<Entity> World::CreateEntity(const Guid &guid)
{
    if (mEntities[guid]) return nullptr;

    auto entity = std::make_shared<Entity>(guid);
    entity->Initialize(this);
    mEntities[guid] = entity;
    return entity;
}

void World::DeleteEntity(const Guid &guid)
{
    auto entity = mEntities[guid];
    if (entity)
    {
        entity->Finalize();
        mEntities.erase(guid);
    }
}

std::shared_ptr<Entity> World::GetEntity(const Guid &guid)
{
    if (!mEntities[guid]) return nullptr;
    return mEntities[guid];
}

size_t World::GetEntityCount()
{
    return mEntities.size();
}

void World::LoadScene(const string &scenePath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
            scenePath,
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType);
    PROJECTENGINE_ASSERT(scene);

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
    {
        auto mesh = scene->mMeshes[i];
        mMeshRenderSystem->LoadMesh(mesh);
    }

    for (unsigned int i = 0; i < scene->mRootNode->mNumChildren; ++i)
    {
        auto child = scene->mRootNode->mChildren[i];
        if (child->mNumMeshes <= 0) continue;

        auto entity = CreateEntity();
        aiVector3D scaling, rotation, position;
        child->mTransformation.Decompose(scaling, rotation, position);

        auto transformation = entity->GetComponent<TransformComponent>();
        transformation->SetPosition(Vector3f(position.x, position.y, position.z));
        transformation->SetRotation(Vector3f(rotation.x, rotation.y, rotation.z));
        transformation->SetScale(Vector3f(scaling.x, scaling.y, scaling.z));

        auto comp = entity->AddComponent<MeshRenderComponent>();

        for (unsigned int j = 0; j < child->mNumMeshes; ++j)
        {
            auto midx = child->mMeshes[j];
            comp->mMeshIdx.push_back(midx);
        }
    }
}

void World::DumpEntities()
{
    cout << "dump entities:" << endl;
    for (auto pair : mEntities) {
        auto guid = pair.first;
        auto entity = pair.second;

        cout << "guid: " << guid << endl;
        cout << "transform component:" << endl;
        auto position = entity->GetComponent<TransformComponent>()->GetPosition();
        cout << "position: " <<  "(" << position.x() << "," << position.y() << "," << position.z() << ")" << endl;

        auto meshRender = entity->GetComponent<MeshRenderComponent>();
        if (meshRender) {
            cout << "MeshRenderComponent:" <<  endl;
            cout << "MeshIndex:";

            for (int i : meshRender->mMeshIdx)
            {
                cout << i << " ";
            }
            cout << "Mesh name:";
            for (int idx : meshRender->mMeshIdx)
            {
                auto mesh = mMeshRenderSystem->mMeshes[idx];
            }
            cout << endl;
        }
        cout << endl;
    }
}

