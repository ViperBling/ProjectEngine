#include "RenderDebugSystem.h"
#include "Framework/Common/Object/World.h"
#include "Framework/Common/Application/Application.h"

ProjectEngine::RenderDebugSystem::RenderDebugSystem(ProjectEngine::World *world) :
    mWorld(world)
{

}

int ProjectEngine::RenderDebugSystem::Initialize() noexcept {

    return 0;
}

void ProjectEngine::RenderDebugSystem::Finalize() noexcept {

    DeleteDebugMesh();
    DeleteDebugAxis();
}

void ProjectEngine::RenderDebugSystem::Render() noexcept {

    auto gfxMgr = mWorld->mApp->mGraphicsManager;

    for (auto & pair : mMeshes) {
        auto mesh = pair.second;
        auto worldMatrix = Matrix4f::Identity();
        mesh->Render(mWorld, worldMatrix);
    }
}

void ProjectEngine::RenderDebugSystem::CreateDebugMesh() noexcept {

    auto gfxMgr = mWorld->mApp->mGraphicsManager;

    unsigned int pointCount = 80;
    std::vector<float> data(3 * pointCount);

    int p = 0;
    for (int x = -10; x <= 10; ++x) {
        if (x == 0) continue;
        data[p * 6] = (float)x;
        data[p * 6 + 1] = 0;
        data[p * 6 + 2] = -10;
        data[p * 6 + 3] = (float)x;
        data[p * 6 + 4] = 0;
        data[p * 6 + 5] = 10;
        p += 1;
    }
    for (int z = -10; z <= 10; ++z) {
        if (z == 0) continue;
        data[p * 6] = -10;
        data[p * 6 + 1] = 0;
        data[p * 6 + 2] = (float)z;
        data[p * 6 + 3] = 10;
        data[p * 6 + 4] = 0;
        data[p * 6 + 5] = (float)z;
        p += 1;
    }

    auto vertexBuffer = gfxMgr->CreateVertexBuffer(data.data(), pointCount, VertexFormat::VF_P3F);

    auto mesh = gfxMgr->CreateRenderMeshDebug(vertexBuffer);
    mesh->mPositions = vertexBuffer;
    mesh->mType = PrimitiveType::PT_LINE;
    mesh->mMaterial->SetShaderParameter("color", Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
    mMeshes["mesh"] = mesh;
}

void ProjectEngine::RenderDebugSystem::DeleteDebugMesh() noexcept {

    auto gfxMgr = mWorld->mApp->mGraphicsManager;

    auto mesh = mMeshes["mesh"];
    if (mesh) {
        mMeshes.erase("mesh");
    }
}

void ProjectEngine::RenderDebugSystem::CreateDebugAxis() noexcept {

    auto gfxMgr = mWorld->mApp->mGraphicsManager;
    std::array<float, 6> x{};
    x[0] = 1000.0f;
    x[1] = 0.0f;
    x[2] = 0.0f;
    x[3] = -1000.0f;
    x[4] = 0.0f;
    x[5] = 0.0f;
    auto vertexBuffer = gfxMgr->CreateVertexBuffer(x.data(), 2, VertexFormat::VF_P3F);
    auto mesh = gfxMgr->CreateRenderMeshDebug(vertexBuffer);
    mesh->mPositions = vertexBuffer;
    mesh->mType = PrimitiveType::PT_LINE;
    mesh->mMaterial->SetShaderParameter("color", Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
    mMeshes["x"] = mesh;

    std::array<float, 6> y{};
    y[0] = 0.0f;
    y[1] = 1000.0f;
    y[2] = 0.0f;
    y[3] = 0.0f;
    y[4] = -1000.0f;
    y[5] = 0.0f;
    auto vertexBuffery = gfxMgr->CreateVertexBuffer(y.data(), 2, VertexFormat::VF_P3F);
    auto meshy = gfxMgr->CreateRenderMeshDebug(vertexBuffery);
    meshy->mPositions = vertexBuffery;
    meshy->mType = PrimitiveType::PT_LINE;
    meshy->mMaterial->SetShaderParameter("color", Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
    mMeshes["y"] = meshy;

    std::array<float, 6> z{};
    z[0] = 0.0f;
    z[1] = 0.0f;
    z[2] = 1000.0f;
    z[3] = 0.0f;
    z[4] = 0.0f;
    z[5] = -1000.0f;
    auto vertexBufferz = gfxMgr->CreateVertexBuffer(z.data(), 2, VertexFormat::VF_P3F);
    auto meshz = gfxMgr->CreateRenderMeshDebug(vertexBufferz);
    meshz->mPositions = vertexBufferz;
    meshz->mType = PrimitiveType::PT_LINE;
    meshz->mMaterial->SetShaderParameter("color", Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
    mMeshes["z"] = meshz;
}

void ProjectEngine::RenderDebugSystem::DeleteDebugAxis() noexcept {

    auto meshx = mMeshes["x"];
    auto meshy = mMeshes["y"];
    auto meshz = mMeshes["z"];
    if (meshx) mMeshes.erase("x");
    if (meshy) mMeshes.erase("y");
    if (meshz) mMeshes.erase("z");
}

