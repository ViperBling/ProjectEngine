#include "MaterialD3D11.h"
#include "Framework/Common/Application/Application.h"
#include "Framework/RHI/D3D11/TextureD3D11.h"
#include "Framework/RHI/D3D11/SamplerStateD3D11.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"

using namespace ProjectEngine;

void MaterialD3D11::Apply(ConstantBuffer cb) noexcept {

    auto gfxD3D11 = dynamic_cast<GraphicsManagerD3D11*>(GApp->mGraphicsManager);

    mShader->Use();
    for (auto& pair : mParameters) {
        if (pair.first == "color") {
            cb.debugColor = pair.second;
        }
    }
    mShader->SetConstantBuffer(cb);

    for (auto& pair : mTexture) {
        if (pair.first == "tBaseMap") {
            auto texture = pair.second;
            auto sampler = mSamplerState[pair.first];
            if (texture && sampler) {
                auto _tex = std::dynamic_pointer_cast<TextureD3D11>(texture);
                auto _samp = std::dynamic_pointer_cast<SamplerStateD3D11>(sampler);
                gfxD3D11->GetDeviceContext()->PSSetShaderResources(0, 1, &(_tex->mSRV));
                gfxD3D11->GetDeviceContext()->PSSetSamplers(0, 1, &(_samp->mSampler));
            }
        }
    }

}
