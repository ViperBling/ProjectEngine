#pragma once

#include <vector>
#include <memory>
#include <string>

#include "IComponent.h"

namespace ProjectEngine
{
    class MeshRenderComponent : public IComponent
    {
    public:
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void Render();
    public:
        void SetVisible(bool v) { mVisible = v; }
        bool IsVisible() { return mVisible; }

    public:
        std::vector<int> mMeshIdx;
        bool mVisible;
    };
}