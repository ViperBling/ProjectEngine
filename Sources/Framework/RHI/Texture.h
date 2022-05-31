#pragma once

#include <string>

#include "Framework/Interface/IResource.h"

namespace ProjectEngine
{
    class Texture : public ITexture
    {
    public:

        virtual void Initialize(const std::string& filePath) noexcept;
        virtual void Finalize() noexcept;
    };
}