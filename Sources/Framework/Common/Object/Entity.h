#pragma once

<<<<<<< HEAD
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "Guid.hpp"
#include "IModule.h"
#include "Components/TransformComponent.h"
#include "Components/MeshRenderComponent.h"
#include "Components/CameraComponent.h"

using namespace xg;
=======
#include "Guid.hpp"
#include "Framework/Interface/IModule.h"
#include "Framework/Common/Object/Components/TransformComponent.h"
#include "Framework/Common/Object/Components/MeshRenderComponent.h"

#include <vector>
>>>>>>> remotes/origin/Branch_Rebase

namespace ProjectEngine
{
    class World;

    class Entity : public IModule
    {
    public:
<<<<<<< HEAD
        virtual int Initialize() noexcept;
        virtual int Initialize(World* world) noexcept;
        virtual void Finalize() noexcept;

    public:
        Entity();
        Entity(const boost::uuids::uuid& guid);
        virtual ~Entity();
        boost::uuids::uuid	GetGuid() const noexcept;
        void	SetGuid(const boost::uuids::uuid& guid) noexcept;

        void	AddChild(std::shared_ptr<Entity> child);
        void	RemoveChild(std::shared_ptr<Entity> child);
        Entity* GetParent();
        void	SetParent(Entity* parent);
        bool	IsChild(std::shared_ptr<Entity> child);
        size_t	GetChildrenCount();

        World*	GetWorld() { return mWorld; }

        template<typename T>T*	AddComponent();
        template<typename T>T*	GetComponent();
        template<typename T>void	RemoveComponent();

    protected:
        boost::uuids::uuid		mGuid;
        Entity*		mParent;
        World*		mWorld;
        std::vector<std::shared_ptr <Entity>>	mChildren;

    protected:
        TransformComponent*		mTransform;
        MeshRenderComponent*	mMeshRender;
        CameraComponent*		mCamera;
    };

    template<typename T>
    T* Entity::AddComponent()
    {
        void* component;
        if (std::is_same<T, TransformComponent>::value)
        {
            mTransform = new TransformComponent();
            mTransform->SetMaster(this);
            mTransform->Initialize();
            component = mTransform;
        }

        if (std::is_same<T, MeshRenderComponent>::value)
        {
            mMeshRender = new MeshRenderComponent;
            mMeshRender->SetMaster(this);
            mMeshRender->Initialize();
            component = mMeshRender;
        }

        if (std::is_same<T, CameraComponent>::value) {
            mCamera = new CameraComponent();
            mCamera->SetMaster(this);
            mCamera->Initialize();
            component = mCamera;
        }

        return (T*)component;
=======
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
        void AddComponent();

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
    void Entity::AddComponent()
    {
        if (std::is_same<T, TransformComponent>::value) {
            mTransform = new TransformComponent();
            mTransform->SetMaster(this);
            mTransform->Initialize();
        }
        else if (std::is_same<T, MeshRenderComponent>::value) {
            mMeshRender = new MeshRenderComponent();
            mMeshRender->SetMaster(this);
            mMeshRender->Initialize();
        }
>>>>>>> remotes/origin/Branch_Rebase
    }

    template<typename T>
    T* Entity::GetComponent()
    {
        void* ret = nullptr;
        if (std::is_same<T, TransformComponent>::value) {
            ret = mTransform;
<<<<<<< HEAD
        }
        else if (std::is_same<T, MeshRenderComponent>::value) {
            ret = mMeshRender;
        }
        else if (std::is_same<T, CameraComponent>::value) {
            ret = mCamera;
        }
=======
        } else if (std::is_same<T, MeshRenderComponent>::value) {
            ret = mMeshRender;
        }

>>>>>>> remotes/origin/Branch_Rebase
        return (T*)ret;
    }

    template<typename T>
    void Entity::RemoveComponent()
    {
        if (std::is_same<T, TransformComponent>::value) {
            delete mTransform;
            mTransform = nullptr;
        }
<<<<<<< HEAD
        if (std::is_same<T, MeshRenderComponent>::value) {
            delete mMeshRender;
            mMeshRender = nullptr;
        }
        if (std::is_same<T, CameraComponent>::value) {
            delete mCamera;
            mCamera = nullptr;
        }
    }
=======
        else if (std::is_same<T, MeshRenderComponent>::value) {
            delete mMeshRender;
            mMeshRender = nullptr;
        }
    }


>>>>>>> remotes/origin/Branch_Rebase
}