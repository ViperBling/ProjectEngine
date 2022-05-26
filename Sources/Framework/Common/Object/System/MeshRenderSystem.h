#pragma once

#include <set>

#include "Guid.hpp"
#include "Framework/Interface/ISystem.h"
#include "Framework/RHI/GraphicsManager.h"
#include "Framework/RHI/RenderMesh.h"
#include "Framework/Common/Object/Components/MeshRenderComponent.h"


namespace ProjectEngine
{
    class World;

    class MeshRenderSystem : public ITickableSystem
    {
    public:
        MeshRenderSystem(World* world);

        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void Tick() noexcept;

    public:
        virtual void AddComponent(MeshRenderComponent* meshRenderComp);
        virtual void DeleteComponent(MeshRenderComponent* meshRenderComp);
        virtual void Render();

        virtual void LoadMesh(aiMesh* mesh);

    public:
        std::vector<std::shared_ptr<RenderMesh>> mMeshes;

    private:
        World* mWorld;
        GraphicsManager* mGraphicsManager;
        std::set<MeshRenderComponent*> mMeshRenderComps;
    };
}