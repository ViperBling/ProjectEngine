#include "RenderDebugSystem.h"
#include "Framework/Common/Object/World.h"
#include "Framework/Common/Application/Application.h"

ProjectEngine::RenderDebugSystem::RenderDebugSystem(ProjectEngine::World *world) :
    mWorld(world)
{
    CreateDebugMesh();
}

int ProjectEngine::RenderDebugSystem::Initialize() noexcept {

    return 0;
}

void ProjectEngine::RenderDebugSystem::Finalize() noexcept {

}

void ProjectEngine::RenderDebugSystem::Render() noexcept {

    auto gfxMgr = mWorld->mApp->mGraphicsManager;

    for (auto & pair : mMeshes) {
        auto mesh = pair.second;
        auto worldMatrix = Matrix4f::Identity();
        mesh->Render(gfxMgr, mWorld, worldMatrix);
    }
}

void ProjectEngine::RenderDebugSystem::CreateDebugMesh() noexcept {

    auto gfxMgr = mWorld->mApp->mGraphicsManager;

    unsigned int pointCount = 84;
    std::vector<float> data(3 * pointCount);

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

    auto vertexBuffer = gfxMgr->CreateVertexBuffer(data.data(), pointCount, VertexFormat::VF_P3F);

    auto mesh = gfxMgr->CreateRenderMeshDebug(vertexBuffer);
    mesh->mPositions = vertexBuffer;
    mesh->mType = PrimitiveType::PT_LINE;
    mMeshes["mesh"] = mesh;
}

void ProjectEngine::RenderDebugSystem::DeleteDebugMesh() noexcept {

    auto gfxMgr = mWorld->mApp->mGraphicsManager;

    auto mesh = mMeshes["mesh"];
    if (mesh) {
        gfxMgr->DeleteRenderMesh(mesh);
        mMeshes.erase("mesh");
    }
}
