#include "WindowsApplication.hpp"
#include <tchar.h>

using namespace ProjectEngine;

// namespace ProjectEngine
// {
//     GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, L"ProjectEngine");
//     WindowsApplication g_App(config);
//     IApplication* g_pApp = &g_App;
// }

int WindowsApplication::Initialize()
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
        _T("ProjectEngine"),      // name of the window class
        m_Config.appName,             // title of the window
        WS_OVERLAPPEDWINDOW,              // window style
        CW_USEDEFAULT,                    // x-position of the window
        CW_USEDEFAULT,                    // y-position of the window
        m_Config.screenWidth,             // width of the window
        m_Config.screenHeight,            // height of the window
        nullptr,                             // we have no parent window, NULL
        nullptr,                             // we aren't using menus, NULL
        hInstance,                        // application handle
        nullptr);                            // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, SW_SHOW);

    return result;
}

void WindowsApplication::Finalize()
{
    
}

void WindowsApplication::Tick()
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

LRESULT WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        case WM_PAINT:
        // we will replace this part with Rendering Module
        {
        } break;
    
        // this message is read when the window is closed
        case WM_DESTROY:
        {
            // close the application entirely
            PostQuitMessage(0);
            BaseApplication::m_bQuit = true;
            return 0;
        }
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}


