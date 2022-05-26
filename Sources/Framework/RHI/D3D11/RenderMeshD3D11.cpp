#include "RenderMeshD3D11.h"
#include "IndexBufferD3D11.h"
#include "VertexBufferD3D11.h"
#include "GraphicsManagerD3D11.h"
#include "Object/World.h"
#include "Application/Application.h"
#include "Platform/Assert.h"

using namespace ProjectEngine;

RenderMeshD3D11::RenderMeshD3D11(aiMesh *mesh)
{
    Initialize(mesh);
}

RenderMeshD3D11::RenderMeshD3D11(std::shared_ptr<VertexBuffer> vb)
{
    Initialize(vb);
}

RenderMeshD3D11::~RenderMeshD3D11()
{
    Finalize();
}

void RenderMeshD3D11::Initialize(aiMesh * mesh) noexcept
{
    if (!mesh) {
        return;
    }
    auto mgrd3d11 = (GraphicsManagerD3D11*)GApp->mGraphicsManager;

    auto count = mesh->mNumVertices;
    if (mesh->HasPositions()) {
        mPositions = mgrd3d11->CreateVertexBuffer(mesh->mVertices, count, VertexFormat::VF_P3F);
    }

    if (mesh->HasNormals()) {
        mNormals = mgrd3d11->CreateVertexBuffer(mesh->mNormals, count, VertexFormat::VF_N3F);
    }

    if (mesh->HasTextureCoords(0)) {
        float *texCoords = (float *)malloc(sizeof(float) * 2 * mesh->mNumVertices);
        for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
            texCoords[k * 2] = mesh->mTextureCoords[0][k].x;
            texCoords[k * 2 + 1] = mesh->mTextureCoords[0][k].y;
        }
        mTexCoords = mgrd3d11->CreateVertexBuffer(texCoords, count, VertexFormat::VF_T2F);
        delete texCoords;
    }

    if (mesh->HasFaces()) {
        unsigned int count = 3 * mesh->mNumFaces;
        unsigned int * idata = new unsigned int[count];
        for (int i = 0; i < mesh->mNumFaces; ++i) {
            auto face = mesh->mFaces[i];
            idata[i * 3] = face.mIndices[0];
            idata[i * 3 + 1] = face.mIndices[1];
            idata[i * 3 + 2] = face.mIndices[2];
        }
        mIndexes = mgrd3d11->CreateIndexBuffer(idata, count, IndexFormat::IF_UINT32);
        delete idata;
    }

    if (mesh->mPrimitiveTypes == aiPrimitiveType::aiPrimitiveType_POINT) {
        mType = PrimitiveType::PT_POINT;
    }
    else if (mesh->mPrimitiveTypes == aiPrimitiveType::aiPrimitiveType_LINE) {
        mType = PrimitiveType::PT_LINE;
    }
    else if (mesh->mPrimitiveTypes == aiPrimitiveType::aiPrimitiveType_TRIANGLE)
    {
        mType = PrimitiveType::PT_TRIANGLE;
    }
    else {
        PROJECTENGINE_ASSERT(false);
    }

    vbcount = GetVaildVertexBufferCount();
    stride = new  unsigned int[vbcount];
    offset = new  unsigned int[vbcount];
    vbuffers = new ID3D11Buffer *[vbcount];
    VertexBufferD3D11* buffer;
    int idx = 0;
    if (mPositions) {
        stride[idx] = mPositions->GetVertexSize(mPositions->mVertexFormat);
        offset[idx] = 0;
        buffer = (VertexBufferD3D11*)mPositions.get();
        vbuffers[idx] = buffer->mVertexBuffer;
        idx += 1;
    }
    if (mNormals) {
        stride[idx] = mNormals->GetVertexSize(mNormals->mVertexFormat);
        offset[idx] = 0;
        buffer = (VertexBufferD3D11*)mNormals.get();
        vbuffers[idx] = buffer->mVertexBuffer;
        idx += 1;
    }
    if (mTexCoords) {
        stride[idx] = mTexCoords->GetVertexSize(mTexCoords->mVertexFormat);
        offset[idx] = 0;
        buffer = (VertexBufferD3D11*)mTexCoords.get();
        vbuffers[idx] = buffer->mVertexBuffer;
        idx += 1;
    }
}

void RenderMeshD3D11::Initialize(std::shared_ptr<VertexBuffer> vb) noexcept
{
    auto mgrd3d11 = (GraphicsManagerD3D11*)GApp->mGraphicsManager;
    mPositions = vb;
    mType = PrimitiveType::PT_LINE;
    vbcount = GetVaildVertexBufferCount();
    stride = new  unsigned int[vbcount];
    offset = new  unsigned int[vbcount];
    vbuffers = new ID3D11Buffer *[vbcount];
    VertexBufferD3D11* buffer;
    int idx = 0;
    if (mPositions) {
        stride[idx] = mPositions->GetVertexSize(mPositions->mVertexFormat);
        offset[idx] = 0;
        buffer = (VertexBufferD3D11*)mPositions.get();
        vbuffers[idx] = buffer->mVertexBuffer;
        idx += 1;
    }
}

void RenderMeshD3D11::Render(World* world, const Matrix4f& worldMatrix) noexcept
{
    auto mgrd3d11 = (GraphicsManagerD3D11*)GApp->mGraphicsManager;
    mgrd3d11->m_deviceContext->IASetVertexBuffers(0, vbcount, vbuffers, stride, offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    if (mIndexes) {
        auto indexBuffer = static_pointer_cast<IndexBufferD3D11>(mIndexes);
        mgrd3d11->m_deviceContext->IASetIndexBuffer(indexBuffer->mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    }

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    if (mType == PrimitiveType::PT_LINE) {
        mgrd3d11->m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
    }
    else if (mType == PrimitiveType::PT_POINT) {
        mgrd3d11->m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
    }
    else if (mType == PrimitiveType::PT_TRIANGLE) {
        mgrd3d11->m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    auto shader = mgrd3d11->UseShader("debug");
    auto camera = world->GetCameraSystem()->GetMainCamera()->GetComponent<CameraComponent>();

    ConstantBuffer cb;
    cb.world = worldMatrix.transpose();
    cb.view = camera->GetViewMatrix().transpose();
    cb.projection = camera->GetPerspectiveMatrix().transpose();
    shader->SetConstantBuffer(cb);

    if (mIndexes) {
        mgrd3d11->DrawIndexed(mIndexes->mCount, 0, 0);
    }
    else {
        mgrd3d11->Draw(mPositions->mCount, 0);
    }

}

void RenderMeshD3D11::Finalize() noexcept
{
    mPositions = nullptr;
    mNormals = nullptr;
    mTexCoords = nullptr;
    mIndexes = nullptr;
}