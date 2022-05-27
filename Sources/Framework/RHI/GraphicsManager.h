#pragma once

#include <memory>
#include <unordered_map>

#include "Framework/Interface/IModule.h"
#include "Framework/Interface/IResource.h"
#include "Framework/RHI/VertexBuffer.h"
#include "Framework/RHI/IndexBuffer.h"
#include "Framework/RHI/RenderMesh.h"
#include "Framework/RHI/Shader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"


namespace ProjectEngine {

    class GraphicsManager : public ITickableModule
    {
    public:
        virtual int Initialize() noexcept = 0;
        virtual void Finalize() noexcept = 0;

        virtual void Present() noexcept = 0;
        virtual void ClearRenderTarget(float r, float g, float b, float a) noexcept = 0;

        virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(void* data, unsigned int count, VertexFormat vf) noexcept = 0;
        virtual void DeleteVertexBuffer(std::shared_ptr<VertexBuffer> vb) noexcept = 0;

        virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(void* data, unsigned int count, IndexFormat iFormat) noexcept = 0;
        virtual void DeleteIndexBuffer(std::shared_ptr<IndexBuffer> ib) noexcept = 0;

        virtual std::shared_ptr<RenderMesh> CreateRenderMesh(aiMesh* mesh) noexcept = 0;
        virtual	std::shared_ptr<RenderMesh>	CreateRenderMeshDebug(std::shared_ptr<VertexBuffer> vb) noexcept = 0;
        virtual void DeleteRenderMesh(std::shared_ptr<RenderMesh> mesh) noexcept = 0;

        virtual void LoadShaders() noexcept = 0;
        virtual std::shared_ptr<Shader> UseShader(const std::string& shaderName) noexcept = 0;

        virtual void Draw(unsigned int vCount, unsigned int start) noexcept = 0;
        virtual void DrawIndexed(unsigned int iCount, unsigned int start, int baseLoc) noexcept = 0;

    protected:

        std::unordered_map<std::string, std::shared_ptr<Shader>> mShaders;
    };
}