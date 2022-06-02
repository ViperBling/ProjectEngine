#include "World.h"
#include "Platform/Assert.h"

#include "Framework/Common/Application/Application.h"
#include "Framework/Common/Object/Components/MeshRenderComponent.h"
#include "Framework/Common/Object/Components/CameraComponent.h"

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <iostream>

using namespace ProjectEngine;


int ProjectEngine::World::Initialize() noexcept {

    mMeshRenderSystem = new MeshRenderSystem(this);
    mMeshRenderSystem->Initialize();

    mCameraSystem = new CameraSystem(this);
    mCameraSystem->Initialize();

    mRenderDebugSystem = new RenderDebugSystem(this);
    mRenderDebugSystem->Initialize();

    return 0;
}

void ProjectEngine::World::Finalize() noexcept {

    mEntities.clear();

    mMeshRenderSystem->Finalize();
    mCameraSystem->Finalize();
}

void ProjectEngine::World::Tick() noexcept {

    mCameraSystem->Tick();
    mMeshRenderSystem->Tick();
}

void ProjectEngine::World::Render() noexcept {

    mApp->mGraphicsManager->ClearRenderTarget(0.2f, 0.2f, 0.2f, 1.0f);
    mMeshRenderSystem->Render();
    mRenderDebugSystem->Render();
    mApp->mGraphicsManager->Present();
}

ProjectEngine::World::World(Application* app) :
    mApp(app),
    mMeshRenderSystem(nullptr)
{

}

std::shared_ptr<ProjectEngine::Entity> ProjectEngine::World::CreateEntity() {

    auto entity = std::make_shared<Entity>();
    entity->Initialize(this);
    mEntities[entity->GetGuid()] = entity;
    return entity;
}

std::shared_ptr<ProjectEngine::Entity> ProjectEngine::World::CreateEntity(const boost::uuids::uuid &guid) {

    if (mEntities[guid]) return nullptr;

    auto entity = std::make_shared<Entity>(guid);
    entity->Initialize(this);
    mEntities[guid] = entity;

    return entity;
}

std::shared_ptr<ProjectEngine::Entity> ProjectEngine::World::GetEntity(const boost::uuids::uuid &guid) {

    if (!mEntities[guid]) return nullptr;
    return mEntities[guid];
}

void ProjectEngine::World::DeleteEntity(const boost::uuids::uuid &guid) {

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

    for (unsigned int j = 0; j < scene->mNumMeshes; ++j) {
        auto mesh = scene->mMeshes[j];
        mMeshRenderSystem->LoadMesh(mesh, scene);
    }

    // build camera
    auto camera = CreateEntity();
    camera->AddComponent<CameraComponent>();
    camera->GetComponent<CameraComponent>()->SetViewWidth((float)mApp->width);
    camera->GetComponent<CameraComponent>()->SetViewHeight((float)mApp->height);
    mCameraSystem->SetMainCamera(camera);

    for (unsigned int i = 0; i < scene->mRootNode->mNumChildren; ++i) {
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

        for (unsigned int j = 0; j < child->mNumMeshes; ++j) {
            auto mIdx = child->mMeshes[j];
            comp->mMeshIdx.emplace_back(mIdx);
        }
    }
}

void World::DumpEntities() {
    using namespace std;

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
            cout << "MeshIndex: ";
            for (auto i : meshRender->mMeshIdx) {
                cout << i << " ";
            }

            // cout << endl;
            // cout << "Mesh name:";
            // for (int i = 0; i < meshRender->mMeshIdx.size(); ++i) {
            //     auto idx = meshRender->mMeshIdx[i];
            //     auto mesh = mMeshRenderSystem->mMeshes[idx];
            // }
            cout << endl;
        }

        auto cameraComponent = entity->GetComponent<CameraComponent>();
        if (cameraComponent) {
            cout << "Camera Type: " << cameraComponent->GetType() << endl;

            cout << cameraComponent->GetViewMatrix() << endl;
            cout << cameraComponent->GetPerspectiveMatrix();
        }

        cout << endl;
    }
}
