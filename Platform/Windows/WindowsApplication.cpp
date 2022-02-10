#include "WindowsApplication.hpp"
#include <tchar.h>

using namespace ProjectEngine;

int ProjectEngine::WindowsApplication::Initialize()
{
    int result;

    result = BaseApplication::Initialize();

    if (result != 0)
        exit(result);

    // Get the HINSTANCE of the Console Program
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    // the handle for the window, filled by a function
    HWND hWnd;
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("ProjectEngine");

    // register the window class
    RegisterClassEx(&wc);

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(
        0,
        "ProjectEngine",      // name of the window class
        m_Config.appName,             // title of the window
        WS_OVERLAPPEDWINDOW,              // window style
        CW_USEDEFAULT,                    // x-position of the window
        CW_USEDEFAULT,                    // y-position of the window
        m_Config.screenWidth,             // width of the window
        m_Config.screenHeight,            // height of the window
        nullptr,                             // we have no parent window, NULL
        nullptr,                             // we aren't using menus, NULL
        hInstance,                        // application handle
        this);                            // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, SW_SHOW);

    m_hWnd = hWnd;

    return result;
}

void ProjectEngine::WindowsApplication::Finalize()
{
    
}

void ProjectEngine::WindowsApplication::Tick()
{
    // this struct holds Windows event messages
    MSG msg;

    // we use PeekMessage instead of GetMessage here
    // because we should not block the thread at anywhere
    // except the engine execution driver module
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK ProjectEngine::WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WindowsApplication* pThis;
    if (message == WM_NCCREATE)
    {
        pThis = static_cast<WindowsApplication*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

        SetLastError(0);
        if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
        {
            if (GetLastError() != 0)
                return FALSE;
        }
    }
    else
    {
        pThis = reinterpret_cast<WindowsApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    // sort through and find what code to run for the message given
    switch(message)
    {
        case WM_KEYDOWN:
        {
            // we will replace this with input manager
            m_bQuit = true;
        }
            break;

            // this message is read when the window is closed
        case WM_DESTROY:
        {
            // close the application entirely
            PostQuitMessage(0);
            m_bQuit = true;
            return 0;
        }
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}


