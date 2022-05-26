#pragma once

#include <string>

namespace ProjectEngine
{
    class GraphicsManager;

    class IShader
    {
    public:
        virtual bool InitializeFromFile(
            GraphicsManager* graphicsManager,
            const std::string& vsPath,
            const std::string& psPath) noexcept = 0;

        virtual void Use(GraphicsManager* graphicsManager) noexcept = 0;
    };
}