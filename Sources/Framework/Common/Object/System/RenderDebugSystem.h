#pragma once

#include <unordered_map>
#include "ISystem.h"
#include "RenderMesh.h"

namespace ProjectEngine
{
    class World;

    class RenderDebugSystem : public IModule
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
        std::unordered_map<std::string, shared_ptr<RenderMesh>> mMeshes;
    };
}