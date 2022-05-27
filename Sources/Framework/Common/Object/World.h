#pragma once

#include "Framework/Interface/IModule.h"
#include "Framework/Common/Object/Entity.h"

#include "Framework/Common/Object/System/MeshRenderSystem.h"
#include "Framework/Common/Object/System/CameraSystem.h"
#include "Framework/Common/Object/System/RenderDebugSystem.h"

#include <boost/functional/hash.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <memory>
#include <unordered_map>
#include <string>


namespace ProjectEngine
{
    class Entity;
    class Application;

    class World : public ITickableModule
    {
    public:
        int Initialize() noexcept override;
        void Finalize() noexcept override;
        void Tick() noexcept override;
        virtual void Render() noexcept;

        World(Application* app);

        std::shared_ptr<ProjectEngine::Entity> CreateEntity();
        std::shared_ptr<ProjectEngine::Entity> CreateEntity(const boost::uuids::uuid& guid);
        std::shared_ptr<ProjectEngine::Entity> GetEntity(const boost::uuids::uuid& guid);
        void DeleteEntity(const boost::uuids::uuid& guid);
        size_t GetEntityCount();

        void LoadScene(const std::string& scenePath);
        void DumpEntities();

        MeshRenderSystem* GetMeshRenderSystem() { return mMeshRenderSystem; }
        CameraSystem* GetCameraSystem() { return mCameraSystem; }
        RenderDebugSystem* GetRenderDebugSystem() { return mRenderDebugSystem; }

    public:
        Application* mApp;

    private:
        std::unordered_map<boost::uuids::uuid, std::shared_ptr<Entity>, boost::hash<boost::uuids::uuid>> mEntities;

        MeshRenderSystem* mMeshRenderSystem;
        CameraSystem* mCameraSystem;
        RenderDebugSystem* mRenderDebugSystem;
    };
}