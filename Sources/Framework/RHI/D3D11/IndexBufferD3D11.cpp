#include "IndexBufferD3D11.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"
#include "Platform/Assert.h"

using namespace ProjectEngine;

void IndexBufferD3D11::Initialize(
    GraphicsManager *gfxManager,
    void *data, unsigned int count,
    IndexFormat iFormat) noexcept
{

    IndexBuffer::Initialize(gfxManager, data, count, iFormat);

    HRESULT hr;

    auto gfxD3D11 = dynamic_cast<GraphicsManagerD3D11*>(gfxManager);
    D3D11_BUFFER_DESC idxBufferDesc;
    D3D11_SUBRESOURCE_DATA idxData;

    // Set up the description of the static index buffer.
    idxBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    idxBufferDesc.ByteWidth = sizeof(unsigned long) * count;
    idxBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    idxBufferDesc.CPUAccessFlags = 0;
    idxBufferDesc.MiscFlags = 0;
    idxBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data.
    idxData.pSysMem = data;
    idxData.SysMemPitch = 0;
    idxData.SysMemSlicePitch = 0;

    hr = gfxD3D11->GetDevice()->CreateBuffer(
        &idxBufferDesc, &idxData, &mIndexBuffer
        );
    if (FAILED(hr)) PROJECTENGINE_ASSERT(false);
}
