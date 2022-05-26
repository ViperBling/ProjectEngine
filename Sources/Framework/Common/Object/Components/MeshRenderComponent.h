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
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void Render();

        void SetVisible(bool visible) { mVisible = visible; }
        bool IsVisible() const { return mVisible; }
        void AddRenderObject(std::string resourePath);

    private:
        bool mVisible;
        std::vector<std::shared_ptr<RenderObject>> mRenderObjects;
    };
}