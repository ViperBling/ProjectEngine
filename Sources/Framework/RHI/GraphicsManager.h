#pragma once

#include "Framework/Interface/IModule.h"
#include "Framework/Common/Singleton.h"

namespace ProjectEngine {

    class GraphicsManager : public ITickableModule
    {
    public:

        virtual void Render() noexcept = 0;
        virtual void ClearRenderTarget(float r, float g, float b, float a) noexcept = 0;
        virtual void CreateDeviceContext() noexcept = 0;
        virtual void ReleaseDeviceContext() noexcept = 0;
    };
}