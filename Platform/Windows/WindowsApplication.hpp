#pragma once

#include <Windows.h>
#include <windowsx.h>
#include "BaseApplication.hpp"

namespace ProjectEngine
{
    class WindowsApplication : public BaseApplication
    {
    public:
        WindowsApplication(GfxConfiguration& config) : BaseApplication(config) {};

        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();

        inline HWND GetMainWindow() const { return m_hWnd; };

    private:
        static LRESULT CALLBACK WindowProc(
                HWND hWnd,
                UINT message,
                WPARAM wParam,
                LPARAM lParam
        );

    private:
        HWND m_hWnd;
    };
}
