#include "RenderMesh.h"
#include "Framework/Common/Object/World.h"
#include "Framework/RHI/GraphicsManager.h"

using namespace ProjectEngine;

RenderMesh::RenderMesh() :
    mPositions(nullptr),
    mNormals(nullptr),
    mTexCoords(nullptr),
    mIndexes(nullptr),
    mType(PrimitiveType::PT_POINT)
{

}

RenderMesh::~RenderMesh()
{

}

void RenderMesh::Initialize(GraphicsManager *gfxManager, aiMesh *mesh) noexcept {

}


void RenderMesh::Initialize(GraphicsManager *gfxManager, std::shared_ptr<VertexBuffer> vb) noexcept
{

}


void RenderMesh::Render(GraphicsManager *gfxManager, World *world, const Matrix4f& worldMatrix) noexcept
{

}

int RenderMesh::GetValidVertexBufferCount() noexcept {

    int result = 0;

    if (mPositions) {
        result++;
    }
    if (mNormals) {
        result++;
    }
    if (mTexCoords) {
        result++;
    }
    return result;
}

