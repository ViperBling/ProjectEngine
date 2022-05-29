#pragma once

#include <Windows.h>
#include "Application.h"
#include "Framework/Common/IO/Keyboard.h"
#include "Framework/Common/IO/Mouse.h"
#include "Singleton.h"

namespace ProjectEngine
{
    class WindowsApplication : public Application
    {
    public:
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void Tick() noexcept;
        virtual void Render() noexcept;

        HWND GetWindowsHandler() noexcept;

        WindowsApplication() {}

    protected:
        // static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;


    private:
        void CreateMainWindow();

    public:
        KeyboardManager* mKbdManager;
        MouseManager* mMouseManager;

    private:
        HWND mHWND{};

        friend class Singleton<WindowsApplication>;
    };

    typedef Singleton<WindowsApplication> GWindowsApplication;
}