#include "Entity.h"

using namespace ProjectEngine;


int Entity::Initialize() noexcept {
    return 0;
}

int Entity::Initialize(World *world) noexcept {
    mWorld = world;

    AddComponent<TransformComponent>();

    return 0;
}

void Entity::Finalize() noexcept {
    mChildren.clear();
    mParent = nullptr;
}

Entity::Entity() :
    mMeshRender(nullptr),
    mCamera(nullptr),
    mTransform(nullptr)
{
    mGuid = boost::uuids::random_generator()();
}

Entity::Entity(const boost::uuids::uuid& guid) :
    mGuid(guid),
    mParent(nullptr),
    mTransform(nullptr)
{
}

Entity::~Entity() {
    std::cout << "Destructor of entity: " << mGuid << std::endl;
}

boost::uuids::uuid Entity::GetGuid() const noexcept {
    return mGuid;
}

void Entity::SetGuid(const boost::uuids::uuid& guid) noexcept {
    mGuid = guid;
}

void Entity::AddChild(std::shared_ptr<Entity> child) {

    if (IsChild(child)) return;

    mChildren.emplace_back(child);
    child->SetParent(this);
}

void Entity::RemoveChild(std::shared_ptr<Entity> child) {

    if (!IsChild(child)) return;

    auto iter = mChildren.begin();
    for (; iter != mChildren.end(); iter++) {
        if ((*iter) == child) {
            mChildren.erase(iter);
            child->SetParent(nullptr);
            return;
        }
    }
}

Entity *Entity::GetParent() {
    return mParent;
}

void Entity::SetParent(Entity *parent) {
    mParent = parent;
}

bool Entity::IsChild(std::shared_ptr<Entity> child) {
    if (child->GetParent() == this) return true;

    return false;
}

size_t Entity::GetChildrenCount() {
    return mChildren.size();
}