#include "WindowsApplication.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"

using namespace ProjectEngine;

int ProjectEngine::WindowsApplication::Initialize() noexcept
{
    CHECK_APPLICATION_INIT(Application::Initialize());
    CreateMainWindow();

    mMemoryManager = new MemoryManager();
    mMemoryManager->Initialize();

    mGraphicsManager = new GraphicsManagerD3D11();
    auto mgr = (GraphicsManagerD3D11*)mGraphicsManager;
    mgr->InitializeWithWindow(mHWND);

    return 0;
}

void ProjectEngine::WindowsApplication::Finalize() noexcept
{
    mGraphicsManager->Finalize();
    mMemoryManager->Finalize();
}

void ProjectEngine::WindowsApplication::Tick() noexcept
{
    Application::Tick();
    MSG msg = {};
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    Render();
}

void ProjectEngine::WindowsApplication::Render() noexcept
{
    mGraphicsManager->Render();
}

HWND ProjectEngine::WindowsApplication::GetWindowsHandler() noexcept
{
    return mHWND;
}

LRESULT ProjectEngine::WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowsApplication* pThis;
    pThis = reinterpret_cast<WindowsApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message)
    {
        case WM_CREATE:
        {
            LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            pThis->Quit();
            return 0;
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

void ProjectEngine::WindowsApplication::CreateMainWindow()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    WNDCLASSEX windowClass = {0};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.lpszClassName = "ProjectEngine";
    RegisterClassEx(&windowClass);

    RECT windowRect = {0, 0, 1280, 720};
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    // Create the window and store a handle to it.
    mHWND = CreateWindow(
            windowClass.lpszClassName,
            "ProjectEngine[Windows]",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            windowRect.right - windowRect.left,
            windowRect.bottom - windowRect.top,
            nullptr,        // We have no parent window.
            nullptr,        // We aren't using menus.
            hInstance,
            this);

    ShowWindow(mHWND, 5);
}
