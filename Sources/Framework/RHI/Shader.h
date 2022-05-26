#pragma once

#include "Framework/Interface/IShader.h"

namespace ProjectEngine
{
    class GraphicsManager;

    class Shader : public IShader
    {
    public:
        virtual bool InitializeFromFile(
            GraphicsManager* graphicsManager,
            const std::string& vsPath,
            const std::string& psPath) noexcept;

        virtual void Use(GraphicsManager* graphicsManager) noexcept;
    };
}