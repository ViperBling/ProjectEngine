#pragma once

#include "Guid.hpp"
#include "Framework/Interface/IModule.h"
#include "Framework/Common/Object/Components/TransformComponent.h"
#include "Framework/Common/Object/Components/MeshRenderComponent.h"

#include <vector>

namespace ProjectEngine
{
    class World;

    class Entity : public IModule
    {
    public:
        int Initialize() noexcept override;
        virtual int Initialize(World* world) noexcept;
        void Finalize() noexcept override;

        Entity();
        Entity(const xg::Guid& guid);
        virtual ~Entity();
        xg::Guid GetGuid() const noexcept;
        void SetGuid(const xg::Guid& guid) noexcept;

        void AddChild(std::shared_ptr<Entity> child);
        void RemoveChild(std::shared_ptr<Entity> child);
        Entity* GetParent();
        void SetParent(Entity* parent);
        bool IsChild(std::shared_ptr<Entity> child);
        size_t GetChildrenCount();

        World* GetWorld() { return mWorld; }

        template<typename T>
        T* AddComponent();

        template<typename T>
        T* GetComponent();

        template<typename T>
        void RemoveComponent();

    protected:
        xg::Guid mGuid;
        Entity* mParent;
        World* mWorld;
        std::vector<std::shared_ptr<Entity>> mChildren;

        TransformComponent* mTransform;
        MeshRenderComponent* mMeshRender;
    };


    template<typename T>
    T* Entity::AddComponent()
    {
        void* comp = nullptr;
        if (std::is_same<T, TransformComponent>::value) {
            mTransform = new TransformComponent();
            mTransform->SetMaster(this);
            mTransform->Initialize();
            comp = mTransform;
        }
        else if (std::is_same<T, MeshRenderComponent>::value) {
            mMeshRender = new MeshRenderComponent();
            mMeshRender->SetMaster(this);
            mMeshRender->Initialize();
            comp = mMeshRender;
        }
        return (T*)comp;
    }

    template<typename T>
    T* Entity::GetComponent()
    {
        void* ret = nullptr;
        if (std::is_same<T, TransformComponent>::value) {
            ret = mTransform;
        } else if (std::is_same<T, MeshRenderComponent>::value) {
            ret = mMeshRender;
        }

        return (T*)ret;
    }

    template<typename T>
    void Entity::RemoveComponent()
    {
        if (std::is_same<T, TransformComponent>::value) {
            delete mTransform;
            mTransform = nullptr;
        }
        else if (std::is_same<T, MeshRenderComponent>::value) {
            delete mMeshRender;
            mMeshRender = nullptr;
        }
    }


}