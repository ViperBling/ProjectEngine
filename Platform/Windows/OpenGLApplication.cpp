#include <iostream>
#include <tchar.h>
#include "OpenGLApplication.hpp"
#include "OpenGL/OpenGLGraphicsManager.hpp"
#include "MemoryManager.hpp"
#include "AssetLoader.hpp"
#include "SceneManager.hpp"
#include "glad/glad_wgl.h"

using namespace ProjectEngine;

namespace ProjectEngine 
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, _T("ProjectEngine (Windows)"));
    IApplication* g_pApp                = static_cast<IApplication*>(new OpenGLApplication(config));
    GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new OpenGLGraphicsManager);
    MemoryManager*   g_pMemoryManager   = static_cast<MemoryManager*>(new MemoryManager);
    AssetLoader*     g_pAssetLoader     = static_cast<AssetLoader*>(new AssetLoader);
    SceneManager*    g_pSceneManager    = static_cast<SceneManager*>(new SceneManager);

}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }

    return 0;
}

int OpenGLApplication::Initialize()
{
    int result;
    auto colorBits = m_Config.redBits + m_Config.greenBits + m_Config.blueBits;

    // create a temporary window for OpenGL context loading
    DWORD Style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    WNDCLASSEX WndClassEx;
    memset(&WndClassEx, 0, sizeof(WNDCLASSEX));

    HINSTANCE hInstance = GetModuleHandle(nullptr);

    WndClassEx.cbSize = sizeof(WNDCLASSEX);
    WndClassEx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    WndClassEx.lpfnWndProc = WndProc;
    WndClassEx.hInstance = hInstance;
    WndClassEx.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    WndClassEx.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    WndClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
    WndClassEx.lpszClassName = _T("InitWindow");

    RegisterClassEx(&WndClassEx);
    HWND TemphWnd = CreateWindowEx(
            WS_EX_APPWINDOW,
            WndClassEx.lpszClassName,
            _T("InitWindow"),
            Style, 0, 0,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            nullptr,
            nullptr,
            hInstance,
            nullptr);

    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = colorBits;
    pfd.cAlphaBits = m_Config.alphaBits;
    pfd.cDepthBits = m_Config.depthBits;
    pfd.cStencilBits = m_Config.stencilBits;
    pfd.iLayerType = PFD_MAIN_PLANE;

    HDC TemphDC = GetDC(TemphWnd);
    // Set a temporary default pixel format.
    int nPixelFormat = ChoosePixelFormat(TemphDC, &pfd);
    if (nPixelFormat == 0) return -1;

    result = SetPixelFormat(TemphDC, nPixelFormat, &pfd);
    if(result != 1)
    {
        return result;
    }

    // Create a temporary rendering context.
    m_RenderContext = wglCreateContext(TemphDC);
    if(!m_RenderContext)
    {
//        printf("wglCreateContext failed!\n");
        std::cout << "wglCreateContext failed!" << std::endl;
        return -1;
    }

    // Set the temporary rendering context as the current rendering context for this window.
    result = wglMakeCurrent(TemphDC, m_RenderContext);
    if(result != 1)
    {
        return result;
    }

    if (!gladLoadWGL(TemphDC))
    {
//        printf("WGL initialize failed!\n");
        std::cout << "WGL initialize failed!" << std::endl;
        result = -1;
    } else {
        result = 0;
//        printf("WGL initialize finished!\n");
        std::cout << "WGL initialize finished!" << std::endl;
    }

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(m_RenderContext);
    ReleaseDC(TemphWnd, TemphDC);
    DestroyWindow(TemphWnd);

    result = WindowsApplication::Initialize();
    if (result)
    {
//        printf("Windows Application initialize failed!");
        std::cout << "Windows Application initialize failed!" << std::endl;
        return result;
    }

    m_hDC  = GetDC(m_hWnd);

    // now we try to init OpenGL Core profile context
    if (GLAD_WGL_ARB_pixel_format && GLAD_WGL_ARB_multisample && GLAD_WGL_ARB_create_context)
    {
        // enable MSAA
        const int attributes[] = {
                WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
                WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
                WGL_COLOR_BITS_ARB,     (int)colorBits,
                WGL_ALPHA_BITS_ARB,     (int)m_Config.alphaBits,
                WGL_DEPTH_BITS_ARB,     (int)m_Config.depthBits,
                WGL_STENCIL_BITS_ARB,   (int)m_Config.stencilBits,
                WGL_SAMPLE_BUFFERS_ARB, 1,
                WGL_SAMPLES_ARB,        4,  // 4x MSAA
                0
        };

        UINT numFormats;

        if(FAILED(wglChoosePixelFormatARB(m_hDC, attributes, nullptr, 1, &nPixelFormat, &numFormats)))
        {
//            printf("wglChoosePixelFormatARB failed!\n");
            std::cout << "wglChoosePixelFormatARB failed!" << std::endl;
            return -1;
        }

        result = SetPixelFormat(m_hDC, nPixelFormat, &pfd);
        if(result != 1)
        {
            return result;
        }

        const int context_attributes[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 2,
                WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0
        };

        m_RenderContext = wglCreateContextAttribsARB(m_hDC, 0, context_attributes);
        if(!m_RenderContext)
        {
//            printf("wglCreateContextAttributeARB failed!\n");
            std::cout << "wglCreateContextAttributeARB failed!" << std::endl;
            return -1;
        }

        result = wglMakeCurrent(m_hDC, m_RenderContext);
        if(result != 1)
        {
            return result;
        }

        result = 0; // we use 0 as success while OpenGL use 1, so convert it
    }
    else
    {
        // Set pixel format.
        int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
        if (nPixelFormat == 0) return -1;

        result = SetPixelFormat(m_hDC, nPixelFormat, &pfd);
        if(result != 1)
        {
            return result;
        }

        // Create rendering context.
        m_RenderContext = wglCreateContext(m_hDC);
        if(!m_RenderContext)
        {
//            printf("wglCreateContext failed!\n");
            std::cout << "wglCreateContext failed!" << std::endl;

            return -1;
        }

        // Set the rendering context as the current rendering context for this window.
        result = wglMakeCurrent(m_hDC, m_RenderContext);
        if(result != 1)
        {
            return result;
        }

        result = 0;
    }

    return result;
}

void OpenGLApplication::Finalize()
{
    if (m_RenderContext) 
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(m_RenderContext);
        m_RenderContext = nullptr;
    }

    WindowsApplication::Finalize();
}

void OpenGLApplication::Tick()
{
    WindowsApplication::Tick();
    g_pGraphicsManager->Clear();
    g_pGraphicsManager->Draw();

    // Present the back buffer to the screen since rendering is complete.
    SwapBuffers(m_hDC);
}

