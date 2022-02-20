#pragma once

#include <set>

#include "Guid.hpp"
#include "ISystem.h"
#include "GraphicsManager.h"
#include "RenderMesh.h"
#include "Object/Components/MeshRenderComponent.h"

using namespace xg;
using namespace std;

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

        virtual void AddComponent(MeshRenderComponent* comp);
        virtual void DeleteComponent(MeshRenderComponent* comp);
        virtual void Render();

        virtual void LoadMesh(aiMesh* mesh);

    public:
        std::vector<shared_ptr<RenderMesh>>	mMeshes;

    private:
        World* mWorld;
        GraphicsManager* mGraphicsManager;
        std::set< MeshRenderComponent*> mComponents;
    };
}