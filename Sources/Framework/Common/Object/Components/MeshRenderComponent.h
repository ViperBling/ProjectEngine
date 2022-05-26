#pragma once

<<<<<<< HEAD
=======
#include "Framework/Interface/IComponent.h"
#include "Framework/RHI/RenderObject.h"

>>>>>>> remotes/origin/Branch_Rebase
#include <vector>
#include <memory>
#include <string>

<<<<<<< HEAD
#include "IComponent.h"

=======
>>>>>>> remotes/origin/Branch_Rebase
namespace ProjectEngine
{
    class MeshRenderComponent : public IComponent
    {
    public:
<<<<<<< HEAD
        MeshRenderComponent() : mVisible(true) {}

        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;

    public:
        void SetVisible(bool v) { mVisible = v; }
        bool IsVisible() { return mVisible; }

    public:
        std::vector<int> mMeshIdx;
        bool mVisible;
=======
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void Render();

        void SetVisible(bool visible) { mVisible = visible; }
        bool IsVisible() const { return mVisible; }
        void AddRenderObject(std::string resourePath);

    private:
        bool mVisible;
        std::vector<std::shared_ptr<RenderObject>> mRenderObjects;
>>>>>>> remotes/origin/Branch_Rebase
    };
}