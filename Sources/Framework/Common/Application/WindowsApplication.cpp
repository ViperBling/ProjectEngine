#include "WindowsApplication.h"

using namespace ProjectEngine;

int ProjectEngine::WindowsApplication::Initialize() noexcept {
    return Application::Initialize();
}

void ProjectEngine::WindowsApplication::Finalize() noexcept {
    Application::Finalize();
}

void ProjectEngine::WindowsApplication::Tick() noexcept {
    Application::Tick();
}

void ProjectEngine::WindowsApplication::Render() noexcept {
    Application::Render();
}

HWND ProjectEngine::WindowsApplication::GetWindowsHandler() noexcept {
    return nullptr;
}

LRESULT ProjectEngine::WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

void ProjectEngine::WindowsApplication::CreateMainWindow() {

}
