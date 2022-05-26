#include <d3d11.h>

#include "VertexBufferD3D11.h"
#include "Framework/RHI/GraphicsManager.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"
#include "Platform/Assert.h"

using namespace ProjectEngine;

void VertexBufferD3D11::Initialize(
    GraphicsManager *graphicsManager,
    void* data,
    unsigned int count,
    VertexFormat vf) noexcept
{
    auto gfxManager = (GraphicsManagerD3D11*)graphicsManager;
    D3D11_BUFFER_DESC vertexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData;

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = this->GetVertexSize(vf) * count;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    vertexData.pSysMem = data;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    gfxManager->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &(this->mVertexBuffer));
}
