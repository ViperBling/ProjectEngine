#pragma once

<<<<<<< HEAD
#include <memory>
#include <unordered_map>
#include <string>
#include <boost/functional/hash.hpp>

#include "IModule.h"
#include "Entity.h"
#include "System/MeshRenderSystem.h"
#include "System/CameraSystem.h"
#include "System/RenderDebugSystem.h"
=======
#include "Framework/Interface/IModule.h"
#include "Framework/Common/Object/Entity.h"

#include "Framework/Common/Object/System/MeshRenderSystem.h"
#include "Guid.hpp"

#include <memory>
#include <unordered_map>
#include <string>

>>>>>>> remotes/origin/Branch_Rebase

namespace ProjectEngine
{
    class Entity;
<<<<<<< HEAD
    class Application;
=======
>>>>>>> remotes/origin/Branch_Rebase

    class World : public ITickableModule
    {
    public:
<<<<<<< HEAD
        virtual int		Initialize() noexcept;
        virtual void	Finalize() noexcept;
        virtual void	Tick() noexcept;
        virtual void	Render() noexcept;

    public:
        World(Application* app);

        std::shared_ptr<Entity> CreateEntity();
        std::shared_ptr<Entity> CreateEntity(const boost::uuids::uuid& guid);
        void DeleteEntity(const boost::uuids::uuid& guid);
        std::shared_ptr<Entity> GetEntity(const boost::uuids::uuid& guid);
        size_t GetEntityCount();

        void LoadScene(const std::string& scenePath);
        void DumpEntities();

        MeshRenderSystem* GetMeshRenderSystem() { return mMeshRenderSystem; }
        CameraSystem* GetCameraSystem() { return mCameraSystem; }
        RenderDebugSystem* GetRenderDebugSystem() { return mRenderDebugSystem; }

    public:
        Application* mApp;

    private:
        std::unordered_map<boost::uuids::uuid, std::shared_ptr<Entity>, boost::hash<boost::uuids::uuid>>	mEntities;

        // systems
        MeshRenderSystem*	mMeshRenderSystem;
        CameraSystem*		mCameraSystem;
        RenderDebugSystem*	mRenderDebugSystem;
=======
        int Initialize() noexcept override;
        void Finalize() noexcept override;
        void Tick() noexcept override;
        virtual void Render() noexcept;

        World();

        std::shared_ptr<ProjectEngine::Entity> CreateEntity();
        std::shared_ptr<ProjectEngine::Entity> CreateEntity(const xg::Guid& guid);
        std::shared_ptr<ProjectEngine::Entity> GetEntity(const xg::Guid& guid);
        void DeleteEntity(const xg::Guid& guid);
        size_t GetEntityCount();

        void LoadScene(std::string scenePath);

        MeshRenderSystem* GetMeshRenderSystem() { return mMeshRenderSystem; }

    private:
        std::unordered_map<xg::Guid, std::shared_ptr<ProjectEngine::Entity>> mEntities;

        MeshRenderSystem* mMeshRenderSystem;
>>>>>>> remotes/origin/Branch_Rebase
    };
}