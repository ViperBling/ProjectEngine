#pragma once

<<<<<<< HEAD
#include <memory>

#include "IModule.h"
#include "IResource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
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

        virtual     std::shared_ptr<VertexBuffer>   CreateVertexBuffer(void* data, int count, VertexFormat vf) noexcept = 0;
        virtual		std::shared_ptr<IndexBuffer>	CreateIndexBuffer(void* data, int count, IndexFormat iformat) noexcept = 0;

        virtual		std::shared_ptr<RenderMesh>		CreateRenderMesh(aiMesh* mesh) noexcept = 0;
        virtual		std::shared_ptr<RenderMesh>		CreateRenderMeshDebug(std::shared_ptr<VertexBuffer> vb) noexcept = 0;

        virtual		void	LoadShaders() noexcept = 0;
        virtual		std::shared_ptr<Shader>	UseShader(const std::string& shaderName) noexcept = 0;

        virtual		void	Draw(unsigned int vcount, unsigned int start) noexcept = 0;
        virtual		void	DrawIndexed(unsigned int icount, unsigned int start, int baseLoc) noexcept = 0;

    protected:
        std::unordered_map<std::string, std::shared_ptr<Shader>>	mShaders;
=======
#include "Framework/Interface/IModule.h"
#include "Framework/Common/Singleton.h"

namespace ProjectEngine {

    class GraphicsManager : public ITickableModule
    {
    public:

        virtual void Render() noexcept = 0;
        virtual void ClearRenderTarget(float r, float g, float b, float a) noexcept = 0;
        virtual void CreateDeviceContext() noexcept = 0;
        virtual void ReleaseDeviceContext() noexcept = 0;
>>>>>>> remotes/origin/Branch_Rebase
    };
}