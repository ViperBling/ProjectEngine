#pragma once

#include <unordered_map>

#include "Framework/Interface/ISystem.h"
#include "Framework/RHI/RenderMesh.h"

namespace ProjectEngine
{
    class World;

    class RenderDebugSystem : ISystem
    {
    public:

        RenderDebugSystem(World* world);
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;

        void Render() noexcept;

        void CreateDebugMesh() noexcept;
        void DeleteDebugMesh() noexcept;

    private:
        World* mWorld;
        std::unordered_map<std::string, std::shared_ptr<RenderMesh>> mMeshes;
    };
}