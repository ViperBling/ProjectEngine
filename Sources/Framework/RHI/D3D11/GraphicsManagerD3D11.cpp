#include "GraphicsManagerD3D11.h"
#include "Platform/Assert.h"

#include <iostream>

int ProjectEngine::GraphicsManagerD3D11::Initialize() noexcept {
    PROJECTENGINE_ASSERT(false);
    return 0;
}

int ProjectEngine::GraphicsManagerD3D11::InitializeWithWindow(HWND hwnd) noexcept {
    m_hwnd = hwnd;
    CreateDeviceContext();
    return 0;
}

void ProjectEngine::GraphicsManagerD3D11::Finalize() noexcept {

}

void ProjectEngine::GraphicsManagerD3D11::Tick() noexcept {

}

void ProjectEngine::GraphicsManagerD3D11::Render() noexcept {

    ClearRenderTarget(0.2f, 0.2f, 0.2f, 1.0f);
    m_swapChain->Present(0, 0);
}

void ProjectEngine::GraphicsManagerD3D11::ClearRenderTarget(float r, float g, float b, float a) noexcept {
    float color[4] = {r, g, b, a};
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

    m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void ProjectEngine::GraphicsManagerD3D11::CreateDeviceContext() noexcept {
    int error;
    unsigned int numModes, i, numerator, denominator;

    HRESULT hr;
    IDXGIFactory* factory;
    IDXGIAdapter* adapter;
    IDXGIOutput* adapterOutput;

    size_t stringLength;
    DXGI_MODE_DESC* displayModeList;
    DXGI_ADAPTER_DESC adapterDesc;

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    D3D_FEATURE_LEVEL featureLevel;
    ID3D11Texture2D* backBufferPtr;

    D3D11_TEXTURE2D_DESC depthBufferDesc;
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    D3D11_RASTERIZER_DESC rasterDesc;
    D3D11_VIEWPORT viewport;
    float fieldOfView, screenAspect;

    // 使用工厂模式创建adapter
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
    PROJECTENGINE_ASSERT(hr >= 0);

    // 枚举主显卡
    hr = factory->EnumAdapters(0, &adapter);
    PROJECTENGINE_ASSERT(hr >= 0);
    hr = adapter->EnumOutputs(0, &adapterOutput);
    PROJECTENGINE_ASSERT(hr >= 0);

    // 获得适配R8G8A8_UNORM的适配器输出格式
    hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
    PROJECTENGINE_ASSERT(hr >= 0);

    displayModeList = new DXGI_MODE_DESC[numModes];
    PROJECTENGINE_ASSERT(displayModeList);

    // 将获得的显示模式输出到hr
    hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
    PROJECTENGINE_ASSERT(hr >= 0);

    for (i = 0; i < numModes; i++) {
        if (displayModeList[i].Width == (unsigned int)1280) {
            if (displayModeList[i].Height == (unsigned int) 720) {
                numerator = displayModeList[i].RefreshRate.Numerator;
                denominator = displayModeList[i].RefreshRate.Denominator;
            }
        }
    }

    hr = adapter->GetDesc(&adapterDesc);
    PROJECTENGINE_ASSERT(hr >= 0);

    m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

    error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);
    PROJECTENGINE_ASSERT(error == 0);
    std::cout << "Video card: " << m_videoCardDescription << std::endl;

    delete[] displayModeList;
    displayModeList = nullptr;

    SAFE_RELEASE_DXOBJ(adapterOutput);
    SAFE_RELEASE_DXOBJ(adapter);
    SAFE_RELEASE_DXOBJ(factory);

    // 初始化swapChain
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

    // 设置1个back buffer
    swapChainDesc.BufferCount = 1;

    swapChainDesc.BufferDesc.Width = 1280;
    swapChainDesc.BufferDesc.Height = 720;

    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    // 设置刷新率，1代表任何可用刷新率
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = m_hwnd;

    //关闭上采样
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    // 设为窗口程序
    swapChainDesc.Windowed = true;

    // 设置扫描线的顺序和缩放为unspecified
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    // 交换缓冲后丢弃back buffer内容
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    // 不设置额外的flag
    swapChainDesc.Flags = 0;

    // 设置FeatureLevel
    featureLevel = D3D_FEATURE_LEVEL_11_1;

    // 创建交换缓冲
    hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE,
        nullptr, 0, &featureLevel, 1,
        D3D11_SDK_VERSION, &swapChainDesc,
        &m_swapChain, &m_device, nullptr, &m_deviceContext);
    PROJECTENGINE_ASSERT(hr >= 0);

    // 获取指向back buffer的指针
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
    PROJECTENGINE_ASSERT(hr >= 0);

    // 创建RT
    hr = m_device->CreateRenderTargetView(backBufferPtr, nullptr, &m_renderTargetView);
    PROJECTENGINE_ASSERT(hr >= 0);

    SAFE_RELEASE_DXOBJ(backBufferPtr);

    // 初始化深度缓冲
    ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

    depthBufferDesc.Width = 1280;
    depthBufferDesc.Height = 720;
    depthBufferDesc.MipLevels = 1;
    depthBufferDesc.ArraySize = 1;
    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.SampleDesc.Count = 1;
    depthBufferDesc.SampleDesc.Quality = 0;
    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDesc.CPUAccessFlags = 0;
    depthBufferDesc.MiscFlags = 0;
    hr = m_device->CreateTexture2D(&depthBufferDesc, nullptr, &m_depthStencilBuffer);
    PROJECTENGINE_ASSERT(hr >= 0);

    // Initialize the description of the stencil state.
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

    // Set up the description of the stencil state.
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    depthStencilDesc.StencilEnable = true;
    depthStencilDesc.StencilReadMask = 0xFF;
    depthStencilDesc.StencilWriteMask = 0xFF;

    // Stencil operations if pixel is front-facing.
    depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // Stencil operations if pixel is back-facing.
    depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // 创建depth stencil state
    hr = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
    PROJECTENGINE_ASSERT(hr >= 0);
    m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

    // Initailze the depth stencil view.
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

    // Set up the depth stencil view description.
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    // Create the depth stencil view.
    hr = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
    PROJECTENGINE_ASSERT(hr >= 0);

    // Bind the render target view and depth stencil buffer to the output render pipeline.
    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

    // Setup the raster description which will determine how and what polygons will be drawn.
    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.CullMode = D3D11_CULL_BACK;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = false;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;

    // Create the rasterizer state from the description we just filled out.
    hr = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
    PROJECTENGINE_ASSERT(hr >= 0);

    // Now set the rasterizer state.
    m_deviceContext->RSSetState(m_rasterState);

    // Setup the viewport for rendering.
    viewport.Width = (float)1280;
    viewport.Height = (float)720;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    // Create the viewport.
    m_deviceContext->RSSetViewports(1, &viewport);
}

void ProjectEngine::GraphicsManagerD3D11::ReleaseDeviceContext() noexcept {

    if (m_swapChain) {
        m_swapChain->SetFullscreenState(false, nullptr);
    }

    SAFE_RELEASE_DXOBJ(m_rasterState);
    SAFE_RELEASE_DXOBJ(m_depthStencilView);
    SAFE_RELEASE_DXOBJ(m_depthStencilState);
    SAFE_RELEASE_DXOBJ(m_depthStencilBuffer);
    SAFE_RELEASE_DXOBJ(m_renderTargetView);
    SAFE_RELEASE_DXOBJ(m_deviceContext);
    SAFE_RELEASE_DXOBJ(m_device);
    SAFE_RELEASE_DXOBJ(m_swapChain);
}
