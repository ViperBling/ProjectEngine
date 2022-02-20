#include <d3d11.h>

#include "VertexBufferD3D11.h"
#include "GraphicsManager.h"
#include "GraphicsManagerD3D11.h"
#include "Application/Application.h"
#include "Platform/Assert.h"

using namespace ProjectEngine;

VertexBufferD3D11::VertexBufferD3D11(void * data, unsigned int count, VertexFormat vf)
{
    Initialize(data, count, vf);
}

VertexBufferD3D11::~VertexBufferD3D11()
{
    Finalize();
}

void VertexBufferD3D11::Initialize(void * data, unsigned int count, VertexFormat vf) noexcept
{
    VertexBuffer::Initialize(data, count, vf);

    auto mgrd3d11 = (GraphicsManagerD3D11*)GApp->mGraphicsManager;
    D3D11_BUFFER_DESC vertexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData;

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = GetVertexSize(vf) * count;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    vertexData.pSysMem = data;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    auto result = mgrd3d11->m_device->CreateBuffer(&vertexBufferDesc, &vertexData, &(this->mVertexBuffer));
}

void VertexBufferD3D11::Finalize() noexcept
{
    if (mVertexBuffer) {
        mVertexBuffer->Release();
    }
}
