#pragma once

#include <Windows.h>
#include "Application.h"
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

    protected:
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        WindowsApplication() = default;
        void CreateMainWindow();

    private:
        HWND mHWND;

        friend class Singleton<WindowsApplication>;
    };
<<<<<<< HEAD
=======

>>>>>>> remotes/origin/Branch_Rebase
    typedef Singleton<WindowsApplication> GWindowsApplication;
}