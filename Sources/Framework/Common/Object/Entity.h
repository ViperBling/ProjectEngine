#pragma once

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

namespace ProjectEngine
{
    class World;

    class Entity : public IModule
    {
    public:
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
    }

    template<typename T>
    T* Entity::GetComponent()
    {
        void* ret = nullptr;
        if (std::is_same<T, TransformComponent>::value) {
            ret = mTransform;
        }
        else if (std::is_same<T, MeshRenderComponent>::value) {
            ret = mMeshRender;
        }
        else if (std::is_same<T, CameraComponent>::value) {
            ret = mCamera;
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
        if (std::is_same<T, MeshRenderComponent>::value) {
            delete mMeshRender;
            mMeshRender = nullptr;
        }
        if (std::is_same<T, CameraComponent>::value) {
            delete mCamera;
            mCamera = nullptr;
        }
    }
}