#include <iostream>

#include "GraphicsManagerD3D11.h"
#include "VertexBufferD3D11.h"
#include "Platform/Assert.h"

using namespace ProjectEngine;

int GraphicsManagerD3D11::Initialize() noexcept
{
    PROJECTENGINE_ASSERT(false);
    return 0;
}

int GraphicsManagerD3D11::InitializeWithWindow(HWND hWnd) noexcept
{
    m_hwnd = hWnd;

    HRESULT result;
    IDXGIFactory* factory;
    IDXGIAdapter* adapter;
    IDXGIOutput* adapterOutput;
    unsigned int numModes, i, numerator, denominator;
    size_t stringLength;
    DXGI_MODE_DESC* displayModeList;
    DXGI_ADAPTER_DESC adapterDesc;
    int error;
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    D3D_FEATURE_LEVEL featureLevel;
    ID3D11Texture2D* backBufferPtr;
    D3D11_TEXTURE2D_DESC depthBufferDesc;
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    D3D11_RASTERIZER_DESC rasterDesc;
    D3D11_VIEWPORT viewport;
    float fieldOfView, screenAspect;

    // Use the factory to create an adapter for the primary graphics interface (video card).
    result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
    PROJECTENGINE_ASSERT(result >= 0);

    // Enumerate the primary adapter output (monitor).
    result = factory->EnumAdapters(0, &adapter);
    PROJECTENGINE_ASSERT(result >= 0);

    // Enumerate the primary adapter output (monitor).
    result = adapter->EnumOutputs(0, &adapterOutput);
    PROJECTENGINE_ASSERT(result >= 0);

    // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
    result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
    PROJECTENGINE_ASSERT(result >= 0);

    // Create a list to hold all the possible display modes for this monitor/video card combination.
    displayModeList = new DXGI_MODE_DESC[numModes];
    PROJECTENGINE_ASSERT(displayModeList);

    result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
    PROJECTENGINE_ASSERT(result >= 0);

    for (i = 0; i < numModes; i++)
    {
        if (displayModeList[i].Width == (unsigned int)1280)
        {
            if (displayModeList[i].Height == (unsigned int)720)
            {
                numerator = displayModeList[i].RefreshRate.Numerator;
                denominator = displayModeList[i].RefreshRate.Denominator;
            }
        }
    }

    result = adapter->GetDesc(&adapterDesc);
    PROJECTENGINE_ASSERT(result >= 0);

    m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

    // Convert the name of the video card to a character array and store it.
    error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);
    PROJECTENGINE_ASSERT(error == 0);
    std::cout << "video card description: " << m_videoCardDescription << std::endl;
    std::cout << "video card memory: " << m_videoCardMemory << std::endl;

    delete[] displayModeList;
    displayModeList = 0;

    SAVE_RELEASE_DXOBJ(adapterOutput);
    SAVE_RELEASE_DXOBJ(adapter);
    SAVE_RELEASE_DXOBJ(factory);

    // Initialize the swap chain description.
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

    // Set to a single back buffer.
    swapChainDesc.BufferCount = 1;

    // Set the width and height of the back buffer.
    swapChainDesc.BufferDesc.Width = 1280;
    swapChainDesc.BufferDesc.Height = 720;

    // Set regular 32-bit surface for the back buffer.
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    // Set the refresh rate of the back buffer.
    if (false)
    {
        swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
    }
    else
    {
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    }

    // Set the usage of the back buffer.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    // Set the handle for the window to render to.
    swapChainDesc.OutputWindow = m_hwnd;

    // Turn multisampling off.
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    // Set to full screen or windowed mode.
    if (false)
    {
        swapChainDesc.Windowed = false;
    }
    else
    {
        swapChainDesc.Windowed = true;
    }

    // Set the scan line ordering and scaling to unspecified.
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    // Discard the back buffer contents after presenting.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    // Don't set the advanced flags.
    swapChainDesc.Flags = 0;

    // Set the feature level to DirectX 11.
    featureLevel = D3D_FEATURE_LEVEL_11_0;

    // Create the swap chain, Direct3D device, and Direct3D device context.
    result = D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE,
            nullptr, 0,
            &featureLevel, 1,
            D3D11_SDK_VERSION,
            &swapChainDesc,
            &m_swapChain, &m_device,
            nullptr, &m_deviceContext);
    PROJECTENGINE_ASSERT(result >= 0);

    // Get the pointer to the back buffer.
    result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
    PROJECTENGINE_ASSERT(result >= 0);

    // Create the render target view with the back buffer pointer.
    result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
    PROJECTENGINE_ASSERT(result >= 0);

    // Release pointer to the back buffer as we no longer need it.
    backBufferPtr->Release();
    backBufferPtr = 0;

    // Initialize the description of the depth buffer.
    ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

    // Set up the description of the depth buffer.
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
    result = m_device->CreateTexture2D(&depthBufferDesc, nullptr, &m_depthStencilBuffer);
    PROJECTENGINE_ASSERT(result >= 0);

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

    // Create the depth stencil state.
    result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
    PROJECTENGINE_ASSERT(result >= 0);
    // Set the depth stencil state.
    m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

    // Initailze the depth stencil view.
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

    // Set up the depth stencil view description.
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    // Create the depth stencil view.
    result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
    PROJECTENGINE_ASSERT(result >= 0);

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
    result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
    PROJECTENGINE_ASSERT(result >= 0);

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
    return 0;
}

void GraphicsManagerD3D11::Finalize() noexcept
{
    if (m_swapChain)
    {
        m_swapChain->SetFullscreenState(false, NULL);
    }
    SAVE_RELEASE_DXOBJ(m_rasterState);
    SAVE_RELEASE_DXOBJ(m_depthStencilView);
    SAVE_RELEASE_DXOBJ(m_depthStencilState);
    SAVE_RELEASE_DXOBJ(m_depthStencilBuffer);
    SAVE_RELEASE_DXOBJ(m_renderTargetView);
    SAVE_RELEASE_DXOBJ(m_deviceContext);
    SAVE_RELEASE_DXOBJ(m_device);
    SAVE_RELEASE_DXOBJ(m_swapChain);
}

void GraphicsManagerD3D11::Tick() noexcept
{

}

void GraphicsManagerD3D11::ClearRenderTarget(float r, float g, float b, float a) noexcept
{
    float color[4] = { r, g, b, a };
    // Clear the back buffer.
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

    // Clear the depth buffer.
    m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

std::shared_ptr<VertexBuffer> GraphicsManagerD3D11::CreateVertexBuffer(void * data, int count, VertexFormat vf) noexcept
{
    auto ptr = std::make_shared<VertexBufferD3D11>(count, vf);

    D3D11_BUFFER_DESC vertexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData;

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = ptr->GetVertexSize(vf) * count;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    vertexData.pSysMem = data;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    auto result = m_device->CreateBuffer(&vertexBufferDesc, &vertexData, &(ptr->mVertexBuffer));
    return ptr;
}

void GraphicsManagerD3D11::DeleteVertexBuffer(std::shared_ptr<VertexBuffer> vb) noexcept
{
    auto ptr = static_pointer_cast<VertexBufferD3D11>(vb);
    if (ptr->mVertexBuffer) {
        ptr->mVertexBuffer->Release();
    }
    ptr->mVertexBuffer = nullptr;
}

std::shared_ptr<RenderMesh> GraphicsManagerD3D11::CreateRenderMesh(aiMesh * mesh) noexcept
{
    auto ptr = std::make_shared<RenderMesh>();
    auto count = mesh->mNumVertices;
    if (mesh->HasPositions()) {
        ptr->mPositions = CreateVertexBuffer(mesh->mVertices, count, VertexFormat::VF_P3F);
    }

    if (mesh->HasNormals()) {
        ptr->mNormals = CreateVertexBuffer(mesh->mNormals, count, VertexFormat::VF_N3F);
    }

    if (mesh->HasTextureCoords(0)) {
        float *texCoords = (float *)malloc(sizeof(float) * 2 * mesh->mNumVertices);
        for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
            texCoords[k * 2] = mesh->mTextureCoords[0][k].x;
            texCoords[k * 2 + 1] = mesh->mTextureCoords[0][k].y;
        }
        ptr->mTexCoords = CreateVertexBuffer(texCoords, count, VertexFormat::VF_T2F);
        delete texCoords;
    }
    return ptr;
}

void GraphicsManagerD3D11::DeleteRenderMesh(std::shared_ptr<RenderMesh> mesh) noexcept
{
    if (mesh->mPositions) {
        DeleteVertexBuffer(mesh->mPositions);
        mesh->mPositions = nullptr;
    }
    if (mesh->mNormals) {
        DeleteVertexBuffer(mesh->mNormals);
        mesh->mNormals = nullptr;
    }
    if (mesh->mTexCoords) {
        DeleteVertexBuffer(mesh->mTexCoords);
        mesh->mTexCoords = nullptr;
    }
}

void GraphicsManagerD3D11::Present() noexcept
{
    if (false){
        // Lock to screen refresh rate.
        m_swapChain->Present(1, 0);
    }
    else{
        // Present as fast as possible.
        m_swapChain->Present(0, 0);
    }
    return;
}