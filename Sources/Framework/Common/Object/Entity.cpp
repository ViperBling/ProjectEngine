#include <type_traits>
#include <iostream>
#include "Entity.h"

using namespace ProjectEngine;

int Entity::Initialize() noexcept
{
    return 0;
}

int Entity::Initialize(World* world) noexcept
{
    mWorld = world;
    AddComponent<TransformComponent>();
    return 0;
}

void Entity::Finalize() noexcept
{
    mChildren.clear();
    mParent = nullptr;
}

Entity::Entity()
{
    mGuid = xg::newGuid();
}

Entity::Entity(const Guid& guid) :
    mGuid(guid),
    mParent(nullptr),
    mTransform(nullptr)
{}

Entity::~Entity()
{
    std::cout << "Destructor of entity: " << mGuid << std::endl;
}

Guid Entity::GetGuid() const noexcept
{
    return mGuid;
}

void Entity::SetGuid(const Guid &guid) noexcept
{
    mGuid = guid;
}

void Entity::AddChild(std::shared_ptr<Entity> child)
{
    if (IsChild(child)) return;
    mChildren.push_back(child);
    child->SetParent(this);
}

void Entity::RemoveChild(std::shared_ptr<Entity> child)
{
    if (!IsChild(child)) return;

    for (auto iter = mChildren.begin(); iter != mChildren.end(); iter++)
    {
        if ((*iter) == child)
        {
            mChildren.erase(iter);
            child->SetParent(nullptr);
            return;
        }
    }
}

bool Entity::IsChild(std::shared_ptr<Entity> child)
{
    if (child->GetParent() == this) return true;
    return false;
}

Entity* Entity::GetParent()
{
    return mParent;
}

void Entity::SetParent(Entity *parent)
{
    mParent = parent;
}

size_t Entity::GetChildrenCount()
{
    return mChildren.size();
}
