#include <d3dcompiler.h>
#include <iostream>

#include "ShaderD3D11.h"
#include "Framework/RHI/GraphicsManager.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"
#include "Platform/Assert.h"


using namespace ProjectEngine;

bool ShaderD3D11::InitializeFromFile(
    GraphicsManager *gfxManager,
    const std::string &vsPath, const std::string &psPath) noexcept
{
    auto gfxManagerD3D11 = dynamic_cast<GraphicsManagerD3D11*>(gfxManager);

    HRESULT hr;

    ID3DBlob* errorMsg;
    ID3DBlob* vsBuffer;
    ID3DBlob* psBuffer;

    std::wstring _vsPath = std::wstring(vsPath.begin(), vsPath.end());
    std::wstring _psPath = std::wstring(psPath.begin(), psPath.end());

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
    dwShaderFlags |= D3DCOMPILE_DEBUG;
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

    hr = D3DCompileFromFile(
        _vsPath.c_str(), nullptr, nullptr, "MainVS", "vs_5_0",
        dwShaderFlags, 0, &vsBuffer, &errorMsg);

    if (FAILED(hr)) {
        OutputDebugStringA(reinterpret_cast<const char*>(errorMsg->GetBufferPointer()));
        std::cout << reinterpret_cast<const char*>(errorMsg->GetBufferPointer()) << std::endl;
        PROJECTENGINE_ASSERT(false);
    }

    hr = D3DCompileFromFile(
        _psPath.c_str(), nullptr, nullptr, "MainPS", "ps_5_0",
        dwShaderFlags, 0, &psBuffer, &errorMsg);

    if (FAILED(hr)) {
        OutputDebugStringA(reinterpret_cast<const char*>(errorMsg->GetBufferPointer()));
        std::cout << reinterpret_cast<const char*>(errorMsg->GetBufferPointer()) << std::endl;
        PROJECTENGINE_ASSERT(false);
    }

    hr = gfxManagerD3D11->GetDevice()->CreateVertexShader(
        vsBuffer->GetBufferPointer(),
        vsBuffer->GetBufferSize(),
        nullptr, &mVertexShader);
    if (FAILED(hr))
    {
        PROJECTENGINE_ASSERT(false);
    }

    hr = gfxManagerD3D11->GetDevice()->CreatePixelShader(
        psBuffer->GetBufferPointer(),
        psBuffer->GetBufferSize(),
        nullptr, &mPixelShader);
    if (FAILED(hr))
    {
        PROJECTENGINE_ASSERT(false);
    }

    std::vector<D3D11_INPUT_ELEMENT_DESC> elementDesc = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    hr = gfxManagerD3D11->GetDevice()->CreateInputLayout(
        elementDesc.data(),
        (UINT)elementDesc.size(),
        vsBuffer->GetBufferPointer(),
        vsBuffer->GetBufferSize(), &mLayout
        );
    if (FAILED(hr)) PROJECTENGINE_ASSERT(false);

    D3D11_BUFFER_DESC matrixBufferDesc;
    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth = sizeof(ConstantBuffer);
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags = 0;
    matrixBufferDesc.StructureByteStride = 0;

    hr = gfxManagerD3D11->GetDevice()->CreateBuffer(
        &matrixBufferDesc, nullptr, &mMatrixBuffer);
    if (FAILED(hr)) PROJECTENGINE_ASSERT(false);

    vsBuffer->Release();
    vsBuffer = nullptr;

    psBuffer->Release();
    psBuffer = nullptr;

    return true;
}

void ShaderD3D11::Use(GraphicsManager *gfxManager) noexcept {

    auto gfxManagerD3D11 = dynamic_cast<GraphicsManagerD3D11*>(gfxManager);

    gfxManagerD3D11->GetDeviceContext()->IASetInputLayout(mLayout);
    gfxManagerD3D11->GetDeviceContext()->VSSetShader(mVertexShader, nullptr, 0);
    gfxManagerD3D11->GetDeviceContext()->PSSetShader(mPixelShader, nullptr, 0);
}

void ShaderD3D11::Finalize(GraphicsManager *gfxManager) noexcept {

    if (mMatrixBuffer) {
        SAFE_RELEASE_DXOBJ(mMatrixBuffer);
    }
    if (mLayout) {
        SAFE_RELEASE_DXOBJ(mLayout);
    }
    if (mPixelShader) {
        SAFE_RELEASE_DXOBJ(mPixelShader);
    }
    if (mVertexShader) {
        SAFE_RELEASE_DXOBJ(mVertexShader);
    }
}

void ShaderD3D11::SetConstantBuffer(GraphicsManager *gfxManager, const ConstantBuffer &cbuffer) noexcept {

    auto gfxManagerD3D11 = dynamic_cast<GraphicsManagerD3D11*>(gfxManager);

    HRESULT hr;

    D3D11_MAPPED_SUBRESOURCE mappedSubresource;
    ConstantBuffer* dataPtr;
    unsigned int bufferNumber;

    // Lock the constant buffer so it can be written to.
    hr = gfxManagerD3D11->GetDeviceContext()->Map(
        mMatrixBuffer, 0,
        D3D11_MAP_WRITE_DISCARD, 0,
        &mappedSubresource);
    if (FAILED(hr)) PROJECTENGINE_ASSERT(false);

    // Copy the matrices into the constant buffer.
    dataPtr = (ConstantBuffer*)mappedSubresource.pData;
    dataPtr->world = cbuffer.world;
    dataPtr->view = cbuffer.view;
    dataPtr->projection = cbuffer.projection;

    // Unlock the constant buffer.
    gfxManagerD3D11->GetDeviceContext()->Unmap(mMatrixBuffer, 0);
    // Set the position of the constant buffer in the vertex shader.
    bufferNumber = 0;
    gfxManagerD3D11->GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &mMatrixBuffer);
}
