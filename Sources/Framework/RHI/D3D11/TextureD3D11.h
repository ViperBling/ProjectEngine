#pragma once

#include <d3d11.h>

#include "Framework/RHI/Texture.h"

namespace ProjectEngine
{
    class TextureD3D11 : public Texture
    {
    public:

        TextureD3D11(const std::string& filePath);
        virtual ~TextureD3D11();

        virtual void Initialize(const std::string& filePath) noexcept;
        virtual void Finalize() noexcept;

    public:

        ID3D11Texture2D* mTexture {};
        ID3D11ShaderResourceView* mSRV {};
    };
}