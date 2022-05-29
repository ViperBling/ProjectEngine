#include "WindowsApplication.h"
#include "Framework/RHI/D3D11/GraphicsManagerD3D11.h"
#include "Framework/Common/Object/World.h"

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

    mTimeManager = new TimeManager();
    mTimeManager->Initialize();

    mKbdManager = new KeyboardManager();
    mKbdManager->Initialize();

    mMouseManager = new MouseManager();
    mMouseManager->Initialize();

    mWorld = new World(this);
    mWorld->Initialize();

    return 0;
}

void ProjectEngine::WindowsApplication::Finalize() noexcept
{
    mWorld->Finalize();

    mGraphicsManager->Finalize();
    mMemoryManager->Finalize();

    mKbdManager->Finalize();
    mMouseManager->Finalize();
}

void ProjectEngine::WindowsApplication::Tick() noexcept
{
    mTimeManager->PreTick();
    Application::Tick();
    MSG msg = {};
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    Render();

    mTimeManager->Tick();
    mTimeManager->PostTick();
}

void ProjectEngine::WindowsApplication::Render() noexcept
{
    mWorld->Render();
}

HWND ProjectEngine::WindowsApplication::GetWindowsHandler() noexcept
{
    return mHWND;
}

void ProjectEngine::WindowsApplication::CreateMainWindow()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    WNDCLASSEX windowClass = {0};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = HandleMsgSetup;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.lpszClassName = "ProjectEngine";
    RegisterClassEx(&windowClass);

    RECT windowRect = {0, 0, width, height};
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    // Create the window and store a handle to it.
    mHWND = CreateWindow(
            windowClass.lpszClassName,
            "ProjectEngine[Windows]",
            WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
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


LRESULT WindowsApplication::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {

    // NCCREATE: Non Client Create，也就不是由客户端创建的，那么就是初始化的时候，这种情况使用自定义的创建方法
    // 通常在窗口第一次创建的时候使用WM_NCCREATE消息
    if (msg == WM_NCCREATE)
    {
        // 从构造参数里面提取指向WindowClass的指针，lpCreateParams就是创建的窗口
        const CREATESTRUCTW * const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        auto* pWnd = static_cast<WindowsApplication*>(pCreate->lpCreateParams);
        // SetWindowLongPtr可以改变窗口属性，也允许用户指向窗口外的数据，这里就是指向的用户的数据，也就是窗口
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        // 然后把消息处理函数替换成我们自己的
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsApplication::HandleMsgThunk));
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }
    // 如果在初始化前接收到了消息，
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WindowsApplication::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {

    // 接收窗口类的指针
    WindowsApplication* pThis;
    pThis = reinterpret_cast<WindowsApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    // 发送消息
    return pThis->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT WindowsApplication::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {

    WindowsApplication* pThis;
    pThis = reinterpret_cast<WindowsApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (msg)
    {
        case WM_CREATE:
        {
            LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
            return 0;
        }
        case WM_CLOSE:
        {
            PostQuitMessage(0);
            pThis->Quit();
            return 0;
        }

            /*********** KEYBOARD MESSAGES ***********/
        case WM_KILLFOCUS:
        {
            mKbdManager->ClearState();
            break;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            if (!(lParam & 0x40000000) || mKbdManager->AutoRepeatIsEnabled()) {
                mKbdManager->OnKeyPressed(static_cast<unsigned char>(wParam));
            }
            break;
        }

        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            mKbdManager->OnKeyReleased(static_cast<unsigned char>(wParam));
            break;
        }
        case WM_CHAR:
        {
            mKbdManager->OnChar(static_cast<char>(wParam));
            break;
        }
            /*********** END KEYBOARD MESSAGES ***********/

            /************* MOUSE MESSAGES ****************/
        case WM_MOUSEMOVE:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            // 在窗口内部时，记录鼠标移动，同时改变鼠标的状态
            if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height) {
                mMouseManager->OnMouseMove(pt.x, pt.y);
                if (!mMouseManager->IsInWindow())
                {
                    SetCapture(hWnd);
                    mMouseManager->OnMouseEnter();
                }
            }
            else {
                // 如果不在窗口内，但是鼠标按键按下，那么也记录鼠标位置
                if (wParam & (MK_LBUTTON | MK_RBUTTON))
                {
                    mMouseManager->OnMouseMove(pt.x, pt.y);
                } else
                {
                    ReleaseCapture();
                    mMouseManager->OnMouseLeave();
                }
            }
            break;
        }
        case WM_LBUTTONDOWN:
        {
            SetForegroundWindow(hWnd);
            const POINTS pt = MAKEPOINTS(lParam);
            mMouseManager->OnLeftPressed(pt.x, pt.y);
            // bring window to foreground on lclick client region
            SetForegroundWindow( hWnd );
            break;
        }
        case WM_RBUTTONDOWN:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mMouseManager->OnRightPressed(pt.x, pt.y);
            break;
        }
        case WM_LBUTTONUP:
        {
            const POINTS pt = MAKEPOINTS(lParam );
            mMouseManager->OnLeftReleased(pt.x, pt.y);
            // release mouse if outside of window
            if(pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
            {
                ReleaseCapture();
                mMouseManager->OnMouseLeave();
            }
            break;
        }
        case WM_RBUTTONUP:
        {
            const POINTS pt = MAKEPOINTS(lParam );
            mMouseManager->OnRightReleased(pt.x, pt.y);
            // release mouse if outside of window
            if(pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height)
            {
                ReleaseCapture();
                mMouseManager->OnMouseLeave();
            }
            break;
        }
        case WM_MOUSEHWHEEL:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
            mMouseManager->OnWheelDelta(pt.x, pt.y, delta);
            break;
        }
        /************** END MOUSE MESSAGES **************/
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);

}
