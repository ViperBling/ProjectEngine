#pragma once

#include "Framework/RHI/GraphicsManager.h"
#include "Framework/Common/Math/MathLib.h"
#include "Framework/Common/Singleton.h"

#include <d3d11.h>
#include <Windows.h>

#define SAFE_RELEASE_DXOBJ(OBJ) { OBJ->Release(); OBJ = 0; }

namespace ProjectEngine
{
    class GraphicsManagerD3D11 : public GraphicsManager
    {
    public:
        int Initialize() noexcept override;
        virtual int InitializeWithWindow(HWND hwnd) noexcept;
        void Finalize() noexcept override;
        void Tick() noexcept override;

        void Render() noexcept override;
        void ClearRenderTarget(float r, float g, float b, float a) noexcept override;
        void CreateDeviceContext() noexcept override;
        void ReleaseDeviceContext() noexcept override;

    protected:
        HWND m_hwnd;

        char m_videoCardDescription[128];
        int m_videoCardMemory;

        IDXGISwapChain*             m_swapChain;
        ID3D11Device*               m_device;
        ID3D11DeviceContext*        m_deviceContext;
        ID3D11RenderTargetView*     m_renderTargetView;
        ID3D11Texture2D*            m_depthStencilBuffer;
        ID3D11DepthStencilState*    m_depthStencilState;
        ID3D11DepthStencilView*     m_depthStencilView;
        ID3D11RasterizerState*      m_rasterState;

    };
}
