#pragma once

#include "Framework/RHI/GraphicsManager.h"
#include "Framework/Common/Math/MathLib.h"
#include "Framework/Common/Utils/Singleton.h"

#include <d3d11.h>
#include <Windows.h>

#define SAFE_RELEASE_DXOBJ(OBJ) { OBJ->Release(); OBJ = 0; }

namespace ProjectEngine
{
    class GraphicsManagerD3D11 : public GraphicsManager
    {
    public:
        GraphicsManagerD3D11(int w, int h) : width(w), height(h) {}

        virtual int Initialize() noexcept;
        virtual int InitializeWithWindow(HWND hwnd) noexcept;
        virtual void Finalize() noexcept;
        virtual void Tick() noexcept;

        virtual void Present() noexcept;
        virtual void ClearRenderTarget(float r, float g, float b, float a) noexcept;

        virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(void* data, unsigned int count, VertexFormat vf) noexcept;

        virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(void* data, unsigned int count, IndexFormat iFormat) noexcept;

        virtual std::shared_ptr<RenderMesh> CreateRenderMesh(aiMesh* mesh, const aiScene* world) noexcept;
        virtual std::shared_ptr<RenderMesh> CreateRenderMeshDebug(std::shared_ptr<VertexBuffer> vb) noexcept;

        virtual std::shared_ptr<Texture> CreateTexture2D(const std::string& path) noexcept;
        virtual std::shared_ptr<SamplerState> CreateSamplerState() noexcept;

        virtual void LoadShaders() noexcept;
        virtual void UseShader(std::shared_ptr<Shader>) noexcept;
        virtual std::shared_ptr<Shader> GetShader(const std::string& shaderName) noexcept;

        virtual void Draw(unsigned int vcount, unsigned int start) noexcept;
        virtual void DrawIndexed(unsigned int icount, unsigned int start, int baseLoc) noexcept;

        ID3D11Device* GetDevice() const { return m_device; }
        ID3D11DeviceContext* GetDeviceContext() const { return m_deviceContext; }

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

    private:
        int width;
        int height;
    };
}
