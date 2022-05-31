#include "SamplerStateD3D11.h"
#include "Platform/Assert.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"
#include "Framework/Common/Application/Application.h"

using namespace ProjectEngine;

SamplerStateD3D11::SamplerStateD3D11() {

    auto gfxD3D11 = dynamic_cast<GraphicsManagerD3D11*>(GApp->mGraphicsManager);

    D3D11_SAMPLER_DESC samplerDesc;

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    auto hr = gfxD3D11->GetDevice()->CreateSamplerState(&samplerDesc, &mSampler);
    if (FAILED(hr)) PROJECTENGINE_ASSERT(false);
}

SamplerStateD3D11::~SamplerStateD3D11() {

    if (mSampler) mSampler->Release();
}

void SamplerStateD3D11::Initialize() noexcept {
}

void SamplerStateD3D11::Finalize() noexcept {
}
