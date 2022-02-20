#include "IndexBufferD3D11.h"
#include "GraphicsManagerD3D11.h"
#include "Application/Application.h"
#include "Platform/Assert.h"

using namespace ProjectEngine;

IndexBufferD3D11::IndexBufferD3D11(void *data, unsigned int count, IndexFormat iFormat)
{
    Initialize(data, count, iFormat);
}

IndexBufferD3D11::~IndexBufferD3D11()
{
    Finalize();
}

void IndexBufferD3D11::Initialize(void *data, unsigned int count, IndexFormat iFormat) noexcept
{
    IndexBuffer::Initialize(data, count, iFormat);

    HRESULT result;
    auto mgrd3d11 = (GraphicsManagerD3D11*)GApp->mGraphicsManager;
    D3D11_BUFFER_DESC indexBufferDesc;
    D3D11_SUBRESOURCE_DATA indexData;

    // Set up the description of the static index buffer
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * count;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data
    indexData.pSysMem = data;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    // Create the index buffer
    result = mgrd3d11->m_device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer);
    if (FAILED(result))
    {
        PROJECTENGINE_ASSERT(false);
    }
}

void IndexBufferD3D11::Finalize() noexcept
{
    if (mIndexBuffer)
    {
        mIndexBuffer->Release();
    }
}