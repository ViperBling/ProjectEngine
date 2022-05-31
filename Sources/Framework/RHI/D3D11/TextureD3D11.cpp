#include "TextureD3D11.h"
#include "Platform/Assert.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"
#include "Framework/Common/Application/Application.h"
#include "Framework/Common/Utils/ImageParser.h"

ProjectEngine::TextureD3D11::TextureD3D11(const std::string &filePath) {

    HRESULT hr;

    auto gfxD3D11 = dynamic_cast<GraphicsManagerD3D11*>(GApp->mGraphicsManager);
    int width, height, channels;
    auto data = ImageParser::Parser(filePath, &width, &height, &channels, 4);

    D3D11_TEXTURE2D_DESC texDesc;
    texDesc.Width = width;
    texDesc.Height = height;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    texDesc.CPUAccessFlags = 0;
    texDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA sd;
    sd.pSysMem = data;
    sd.SysMemPitch = width * sizeof(uint32_t);
    sd.SysMemSlicePitch = width * height * sizeof(uint32_t);

    hr = gfxD3D11->GetDevice()->CreateTexture2D(&texDesc, &sd, &mTexture);
    if (FAILED(hr)) PROJECTENGINE_ASSERT(false);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    srvDesc.Texture2D.MostDetailedMip = 0;

    hr = gfxD3D11->GetDevice()->CreateShaderResourceView(mTexture, &srvDesc, &mSRV);
    if (FAILED(hr)) PROJECTENGINE_ASSERT(false);
}

ProjectEngine::TextureD3D11::~TextureD3D11() {

    if (mSRV)  mSRV->Release();
    if (mTexture) mTexture->Release();

    mSRV = nullptr;
    mTexture = nullptr;
}

void ProjectEngine::TextureD3D11::Initialize(const std::string &filePath) noexcept {

}

void ProjectEngine::TextureD3D11::Finalize() noexcept {

}
