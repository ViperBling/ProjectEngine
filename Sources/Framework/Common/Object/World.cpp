<<<<<<< HEAD
#include <iostream>

#include "Platform/Assert.h"
#include "Application/Application.h"
#include "World.h"
#include "Components/MeshRenderComponent.h"

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

using namespace std;
using namespace ProjectEngine;

World::World(Application *app) :
    mApp(app),
    mMeshRenderSystem(nullptr),
    mCameraSystem(nullptr),
    mRenderDebugSystem(nullptr)
{}

int World::Initialize() noexcept
{
    mMeshRenderSystem = new MeshRenderSystem(this);
    mMeshRenderSystem->Initialize();

    mCameraSystem = new CameraSystem(this);
    mCameraSystem->Initialize();

    mRenderDebugSystem = new RenderDebugSystem(this);
    mRenderDebugSystem->Initialize();

    return 0;
}

void World::Finalize() noexcept
{
    mEntities.clear();
    mMeshRenderSystem->Finalize();
    mCameraSystem->Finalize();
//    mRenderDebugSystem->Finalize();
}

void World::Tick() noexcept
{
    mMeshRenderSystem->Tick();
}

void World::Render() noexcept
{
    mApp->mGraphicsManager->ClearRenderTarget(0.2f, 0.4f, 0.6f, 1.0f);

    mMeshRenderSystem->Render();
    mRenderDebugSystem->Render();
    mApp->mGraphicsManager->Present();
}

std::shared_ptr<Entity> World::CreateEntity()
{
=======
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

>>>>>>> remotes/origin/Branch_Rebase
    auto entity = std::make_shared<Entity>();
    entity->Initialize(this);
    mEntities[entity->GetGuid()] = entity;
    return entity;
}

<<<<<<< HEAD
std::shared_ptr<Entity> World::CreateEntity(const boost::uuids::uuid &guid)
{
=======
std::shared_ptr<ProjectEngine::Entity> ProjectEngine::World::CreateEntity(const xg::Guid &guid) {

>>>>>>> remotes/origin/Branch_Rebase
    if (mEntities[guid]) return nullptr;

    auto entity = std::make_shared<Entity>(guid);
    entity->Initialize(this);
    mEntities[guid] = entity;
<<<<<<< HEAD
    return entity;
}

void World::DeleteEntity(const boost::uuids::uuid &guid)
{
    auto entity = mEntities[guid];
    if (entity)
    {
=======

    return entity;
}

std::shared_ptr<ProjectEngine::Entity> ProjectEngine::World::GetEntity(const xg::Guid &guid) {

    return mEntities[guid];
}

void ProjectEngine::World::DeleteEntity(const xg::Guid &guid) {

    auto entity = mEntities[guid];
    if (entity) {
>>>>>>> remotes/origin/Branch_Rebase
        entity->Finalize();
        mEntities.erase(guid);
    }
}

<<<<<<< HEAD
std::shared_ptr<Entity> World::GetEntity(const boost::uuids::uuid &guid)
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

    // build main camera
    auto camera = CreateEntity();
    camera->AddComponent<CameraComponent>();
    mCameraSystem->SetMainCamera(camera);


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

=======
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
>>>>>>> remotes/origin/Branch_Rebase
