#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"

#include "Framework/Interface/IResource.h"
#include "Framework/RHI/VertexBuffer.h"
#include "Framework/RHI/IndexBuffer.h"

#include <memory>

//using namespace std;

namespace ProjectEngine
{
    class GraphicsManager;

    class RenderMesh : public IMesh
    {
    public:
        RenderMesh();
        virtual ~RenderMesh();

        virtual void Initialize(GraphicsManager* gfxManager, aiMesh* mesh) noexcept;
        virtual void Initialize(GraphicsManager* gfxManager, std::shared_ptr<VertexBuffer> vb) noexcept;
        virtual void Render(GraphicsManager* gfxManager, World* world, const Matrix4f& worldMatrix) noexcept;
        virtual int GetValidVertexBufferCount() noexcept;

    public:
        std::shared_ptr<VertexBuffer>    mPositions;
        std::shared_ptr<VertexBuffer>    mNormals;
        std::shared_ptr<VertexBuffer>    mTexCoords;
        std::shared_ptr<IndexBuffer>     mIndexes;
        PrimitiveType                    mType;
    };
}