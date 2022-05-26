#include <d3dcompiler.h>
#include <iostream>

#include "ShaderD3D11.h"
#include "Framework/RHI/GraphicsManager.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"
#include "Platform/Assert.h"


using namespace ProjectEngine;

bool ShaderD3D11::InitializeFromFile(
    GraphicsManager *graphicsManager,
    const std::string &vsPath, const std::string &psPath) noexcept
{
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

    return true;
}

void ShaderD3D11::Use(GraphicsManager *graphicsManager) noexcept {


}
