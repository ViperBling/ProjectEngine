#pragma once

<<<<<<< HEAD
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

=======
#include "Guid.hpp"
#include "Framework/Interface/ISystem.h"
#include "Framework/Common/Object/Components/MeshRenderComponent.h"

#include <set>

namespace ProjectEngine
{
    class MeshRenderSystem : public ITickableSystem
    {
    public:
>>>>>>> remotes/origin/Branch_Rebase
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void Tick() noexcept;

<<<<<<< HEAD
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
=======
    public:
        virtual void AddComponent(MeshRenderComponent* meshRenderComp);
        virtual void DeleteComponent(MeshRenderComponent* meshRenderComp);
        virtual void Render();

    private:
        std::set<MeshRenderComponent*> mMeshRenderComps;
>>>>>>> remotes/origin/Branch_Rebase
    };
}