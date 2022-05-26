#pragma once

#include "Guid.hpp"
#include "Framework/Interface/ISystem.h"
#include "Framework/Common/Object/Components/MeshRenderComponent.h"

#include <set>

namespace ProjectEngine
{
    class MeshRenderSystem : public ITickableSystem
    {
    public:
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void Tick() noexcept;

    public:
        virtual void AddComponent(MeshRenderComponent* meshRenderComp);
        virtual void DeleteComponent(MeshRenderComponent* meshRenderComp);
        virtual void Render();

    private:
        std::set<MeshRenderComponent*> mMeshRenderComps;
    };
}