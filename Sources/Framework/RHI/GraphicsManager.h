#pragma once

#include <memory>

#include "IModule.h"
#include "IResource.h"
#include "VertexBuffer.h"
#include "RenderMesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"

namespace ProjectEngine
{
    class GraphicsManager : public ITickableModule
    {
    public:
        virtual int Initialize() noexcept = 0;
        virtual void Finalize() noexcept = 0;

        virtual void Present() noexcept = 0;
        virtual void ClearRenderTarget(float r, float g, float b, float a) noexcept = 0;

        virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(void* data, int count, VertexFormat vf) noexcept = 0;
        virtual		void	DeleteVertexBuffer(std::shared_ptr<VertexBuffer> vb) noexcept = 0;

        virtual		std::shared_ptr<RenderMesh>		CreateRenderMesh(aiMesh* mesh) noexcept = 0;
        virtual		void	DeleteRenderMesh(std::shared_ptr<RenderMesh> mesh) noexcept = 0;
    };
}