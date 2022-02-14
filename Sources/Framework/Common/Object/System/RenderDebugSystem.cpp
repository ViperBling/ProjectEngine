#include "RenderDebugSystem.h"
#include "Object/World.h"
#include "Application/Application.h"

using namespace ProjectEngine;

RenderDebugSystem::RenderDebugSystem(World *world) : mWorld(world) {}

int RenderDebugSystem::Initialize() noexcept
{
    return 0;
}

void RenderDebugSystem::Finalize() noexcept
{

}

void RenderDebugSystem::Render() noexcept
{
    auto manager = mWorld->mApp->mGraphicsManager;

    for (auto pair : mMeshes)
    {
        auto mesh = pair.second;
        auto worldMatrix = Matrix4f::Identity();
        mesh->Render(mWorld, worldMatrix);
    }
}

void RenderDebugSystem::CreateDebugMesh() noexcept
{
    auto manager = mWorld->mApp->mGraphicsManager;

    unsigned int pointCount = 84;
    float* data = new float[3 * pointCount];

    int p = 0;
    for (int x = -10; x <= 10; ++x) {
        data[p * 6] = x;
        data[p * 6 + 1] = 0;
        data[p * 6 + 2] = -10;
        data[p * 6 + 3] = x;
        data[p * 6 + 4] = 0;
        data[p * 6 + 5] = 10;
        p += 1;
    }
    for (int z = -10; z <= 10; ++z) {
        data[p * 6] = -10;
        data[p * 6 + 1] = 0;
        data[p * 6 + 2] = z;
        data[p * 6 + 3] = 10;
        data[p * 6 + 4] = 0;
        data[p * 6 + 5] = z;
        p += 1;
    }

    auto vertexBuffer = manager->CreateVertexBuffer(data, pointCount, VertexFormat::VF_P3F);
    delete[] data;

    auto mesh = manager->CreateRenderMeshDebug(vertexBuffer);
    mesh->mPositions = vertexBuffer;
    mesh->mType = PrimitiveType::PT_LINE;
    mMeshes["mesh"] = mesh;
}

void RenderDebugSystem::DeleteDebugMesh() noexcept
{
    auto manager = mWorld->mApp->mGraphicsManager;

    auto mesh = mMeshes["mesh"];
    if (mesh)
    {
        mMeshes.erase("mesh");
    }
}