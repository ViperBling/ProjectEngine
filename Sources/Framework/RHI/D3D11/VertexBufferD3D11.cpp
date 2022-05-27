#include <d3d11.h>

#include "VertexBufferD3D11.h"
#include "Framework/Common/Application/Application.h"
#include "Framework/RHI/GraphicsManager.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"
#include "Platform/Assert.h"

using namespace ProjectEngine;


VertexBufferD3D11::VertexBufferD3D11(void *data, unsigned int count, VertexFormat vf) noexcept {

    VertexBuffer::Initialize(data, count, vf);

    auto gfxManagerD3D11 = dynamic_cast<GraphicsManagerD3D11*>(GApp->mGraphicsManager);
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

    gfxManagerD3D11->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &(this->mVertexBuffer));
}

VertexBufferD3D11::~VertexBufferD3D11() {

    if (mVertexBuffer) {
        mVertexBuffer->Release();
    }
}


void VertexBufferD3D11::Initialize(void* data, unsigned int count, VertexFormat vf) noexcept
{

}


void VertexBufferD3D11::Finalize() noexcept {


}
