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

    class RenderMesh : public IMesh
    {
    public:
        RenderMesh();
        virtual ~RenderMesh();

        virtual void Initialize(std::shared_ptr<VertexBuffer> vb) noexcept;
        virtual void Render(World* world, const Matrix4f& worldMatrix) noexcept;
        virtual int GetValidVertexBufferCount() noexcept;
        virtual void Finalize() noexcept;

    public:
        std::shared_ptr<VertexBuffer>    mPositions;
        std::shared_ptr<VertexBuffer>    mNormals;
        std::shared_ptr<VertexBuffer>    mTexCoords;
        std::shared_ptr<IndexBuffer>     mIndexes;
        PrimitiveType                    mType;
        std::string                      mMeshName;
    };
}