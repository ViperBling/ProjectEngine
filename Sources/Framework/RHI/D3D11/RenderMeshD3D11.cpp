#include "RenderMeshD3D11.h"
#include "Framework/Common/Application/Application.h"
#include "Framework/RHI/D3D11/IndexBufferD3D11.h"
#include "Framework/RHI/D3D11/VertexBufferD3D11.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"
#include "Framework/Common/Object/World.h"
#include "Platform/Assert.h"

using namespace ProjectEngine;

RenderMeshD3D11::RenderMeshD3D11(aiMesh *mesh) {

    if (!mesh) return;

    auto gfxMgrD3D11 = dynamic_cast<GraphicsManagerD3D11*>(GApp->mGraphicsManager);

    auto count = mesh->mNumVertices;

    if (mesh->HasPositions()) {
        mPositions = gfxMgrD3D11->CreateVertexBuffer(
            mesh->mVertices, count, VertexFormat::VF_P3F
        );
    }
    if (mesh->HasNormals()) {
        mNormals = gfxMgrD3D11->CreateVertexBuffer(
            mesh->mNormals, count, VertexFormat::VF_N3F);
    }
    if (mesh->HasTextureCoords(0)) {
        std::vector<float> texCoords(sizeof(float) * 2 * mesh->mNumVertices);
        for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
            texCoords[k * 2] = mesh->mTextureCoords[0][k].x;
            texCoords[k * 2 + 1] = mesh->mTextureCoords[0][k].y;
        }
        mTexCoords = gfxMgrD3D11->CreateVertexBuffer(texCoords.data(), count, VertexFormat::VF_T2F);
    }

    if (mesh->HasFaces()) {
        unsigned int iCount = 3 * mesh->mNumFaces;
        std::vector<unsigned int> iData(iCount);
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            auto face = mesh->mFaces[i];
            iData[i * 3] = face.mIndices[0];
            iData[i * 3 + 1] = face.mIndices[1];
            iData[i * 3 + 2] = face.mIndices[2];
        }
        mIndexes = gfxMgrD3D11->CreateIndexBuffer(iData.data(), iCount, IndexFormat::IF_UINT32);
    }

    if (mesh->mPrimitiveTypes == aiPrimitiveType::aiPrimitiveType_POINT) {
        mType = PrimitiveType::PT_POINT;
    }
    else if (mesh->mPrimitiveTypes == aiPrimitiveType::aiPrimitiveType_LINE) {
        mType = PrimitiveType::PT_LINE;
    }
    else if (mesh->mPrimitiveTypes == aiPrimitiveType::aiPrimitiveType_TRIANGLE) {
        mType = PrimitiveType::PT_TRIANGLE;
    }
    else {
        PROJECTENGINE_ASSERT(false);
    }

    vbcount = this->GetValidVertexBufferCount();
    stride.resize(vbcount);
    offset.resize(vbcount);
    vBuffers.resize(vbcount);

    VertexBufferD3D11* buffer;

    int idx = 0;
    if (mPositions) {
        stride[idx] = mPositions->GetVertexSize(mPositions->GetVertexFormat());
        offset[idx] = 0;

        buffer = dynamic_cast<VertexBufferD3D11*>(mPositions.get());
        vBuffers[idx] = buffer->mVertexBuffer;

        idx++;
    }

    if (mNormals) {
        stride[idx] = mNormals->GetVertexSize(mNormals->GetVertexFormat());
        offset[idx] = 0;

        buffer = dynamic_cast<VertexBufferD3D11*>(mNormals.get());
        vBuffers[idx] = buffer->mVertexBuffer;

        idx++;
    }

    if (mTexCoords) {
        stride[idx] = mTexCoords->GetVertexSize(mTexCoords->GetVertexFormat());
        offset[idx] = 0;

        buffer = dynamic_cast<VertexBufferD3D11*>(mTexCoords.get());
        vBuffers[idx] = buffer->mVertexBuffer;

        idx++;
    }

    mMaterial = std::make_shared<Material>();
    auto shader = gfxMgrD3D11->GetShader("pbr");
    mMaterial->SetShader(shader);
}

RenderMeshD3D11::RenderMeshD3D11(std::shared_ptr<VertexBuffer> vb) {

    auto gfxMgrD3D11 = dynamic_cast<GraphicsManagerD3D11*>(GApp->mGraphicsManager);

    mPositions = vb;
    mType = PrimitiveType::PT_LINE;
    vbcount = this->GetValidVertexBufferCount();

    stride.resize(vbcount);
    offset.resize(vbcount);
    vBuffers.resize(vbcount);

    VertexBufferD3D11* buffer;

    int idx = 0;
    if (mPositions) {
        stride[idx] = mPositions->GetVertexSize(mPositions->GetVertexFormat());
        offset[idx] = 0;

        buffer = dynamic_cast<VertexBufferD3D11*>(mPositions.get());
        vBuffers[idx] = buffer->mVertexBuffer;

        idx++;
    }

    mMaterial = std::make_shared<Material>();
    auto shader = gfxMgrD3D11->GetShader("debug");
    mMaterial->SetShader(shader);
}

RenderMeshD3D11::~RenderMeshD3D11() {

    mPositions = nullptr;
    mNormals = nullptr;
    mTexCoords = nullptr;
    mIndexes = nullptr;
}

void RenderMeshD3D11::Initialize(aiMesh *mesh) noexcept {

}

void RenderMeshD3D11::Initialize(std::shared_ptr<VertexBuffer> vb) noexcept {

}

void RenderMeshD3D11::Render(World *world, const Matrix4f& worldMatrix) noexcept {

    auto gfxManagerD3D11 = dynamic_cast<GraphicsManagerD3D11*>(GApp->mGraphicsManager);

    gfxManagerD3D11->GetDeviceContext()->IASetVertexBuffers(0, vbcount, vBuffers.data(), stride.data(), offset.data());

    if (mIndexes) {
        auto indexBuffer = std::static_pointer_cast<IndexBufferD3D11>(mIndexes);
        gfxManagerD3D11->GetDeviceContext()->IASetIndexBuffer(indexBuffer->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
    }

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    if (mType == PrimitiveType::PT_LINE) {
        gfxManagerD3D11->GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
    }
    else if (mType == PrimitiveType::PT_POINT) {
        gfxManagerD3D11->GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
    }
    else if (mType == PrimitiveType::PT_TRIANGLE) {
        gfxManagerD3D11->GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    auto camera = world->GetCameraSystem()->GetMainCamera()->GetComponent<CameraComponent>();

    ConstantBuffer cb;
    cb.world = worldMatrix.transpose();
    cb.view = camera->GetViewMatrix().transpose();
    cb.projection = camera->GetPerspectiveMatrix().transpose();
    mMaterial->Apply(cb);

    if (mIndexes) {
        gfxManagerD3D11->DrawIndexed(mIndexes->GetCount(), 0, 0);
    }
    else {
        gfxManagerD3D11->Draw(mPositions->GetCount(), 0);
    }
}



void RenderMeshD3D11::Finalize() noexcept {

}



