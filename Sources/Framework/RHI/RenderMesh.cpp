#include "RenderMesh.h"
#include "GraphicsManager.h"
#include "Object/World.h"

using namespace ProjectEngine;

RenderMesh::RenderMesh() :
    mPositions(nullptr),
    mNormals(nullptr),
    mTexCoords(nullptr),
    mIndexes(nullptr),
    mType(PrimitiveType::PT_POINT)
{}

RenderMesh::~RenderMesh() {}

void RenderMesh::Initialize(std::shared_ptr<VertexBuffer> vb) noexcept {}

void RenderMesh::Render(World* world, const Matrix4f& worldMatrix) noexcept {}

int RenderMesh::GetVaildVertexBufferCount() noexcept
{
    int result = 0;
    if (mPositions)
    {
        result += 1;
    }
    if (mNormals)
    {
        result += 1;
    }
    if (mTexCoords)
    {
        result += 1;
    }

    return result;
}

void RenderMesh::Finialize() noexcept {}