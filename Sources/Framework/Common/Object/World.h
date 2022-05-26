#pragma once

#include "Framework/Interface/IModule.h"
#include "Framework/Common/Object/Entity.h"

#include "Framework/Common/Object/System/MeshRenderSystem.h"
#include "Guid.hpp"

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
        std::shared_ptr<ProjectEngine::Entity> CreateEntity(const xg::Guid& guid);
        std::shared_ptr<ProjectEngine::Entity> GetEntity(const xg::Guid& guid);
        void DeleteEntity(const xg::Guid& guid);
        size_t GetEntityCount();

        void LoadScene(const std::string& scenePath);
        void DumpEntities();

        MeshRenderSystem* GetMeshRenderSystem() { return mMeshRenderSystem; }

    public:
        Application* mApp;

    private:
        std::unordered_map<xg::Guid, std::shared_ptr<ProjectEngine::Entity>> mEntities;

        MeshRenderSystem* mMeshRenderSystem;
    };
}