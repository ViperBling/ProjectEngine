#include "MeshRenderComponent.h"
#include "Object/Entity.h"
#include "Object/World.h"

using namespace ProjectEngine;

int MeshRenderComponent::Initialize() noexcept
{
    auto master = GetMaster();
    if (master)
    {
        auto world = master->GetWorld();
        if (world)
        {
            world->GetMeshRenderSystem()->AddComponent(this);
        }
    }
    return 0;
}

void MeshRenderComponent::Finalize() noexcept
{
    auto master = GetMaster();
    if (master)
    {
        auto world = master->GetWorld();
        if (world)
        {
            world->GetMeshRenderSystem()->DeleteComponent(this);
        }
    }
}