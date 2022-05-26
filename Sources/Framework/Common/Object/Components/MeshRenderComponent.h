#pragma once

#include "Framework/Interface/IComponent.h"
#include "Framework/RHI/RenderObject.h"

#include <vector>
#include <memory>
#include <string>

namespace ProjectEngine
{
    class MeshRenderComponent : public IComponent
    {
    public:
        int Initialize() noexcept override;
        void Finalize() noexcept override;
        virtual void Render();

        void SetVisible(bool visible) { mVisible = visible; }
        bool IsVisible() const { return mVisible; }
        std::shared_ptr<RenderObject> AddRenderObject();
        std::shared_ptr<RenderObject> GetRenderObject(int idx);
        size_t GetRenderObjectCount();

    private:
        bool mVisible;
        std::vector<std::shared_ptr<RenderObject>> mRenderObjects;
    };
}