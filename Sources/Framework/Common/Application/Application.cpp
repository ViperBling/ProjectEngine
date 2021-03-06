#include "Application.h"

using namespace ProjectEngine;

int Application::Initialize() noexcept {
    mQuit = false;
    mMemoryManager = nullptr;
    mGraphicsManager = nullptr;
    mWorld = nullptr;
    mKbdManager = nullptr;
    mMouseManager = nullptr;

    return 0;
}

void Application::Tick() noexcept{

}

void Application::Render() noexcept{

}

void Application::Run() noexcept{

    while (!IsQuit())
    {
        Tick();
        Render();
    }
}

void Application::Finalize() noexcept {
}

bool Application::IsQuit() noexcept {
    return mQuit;
}

void Application::SetSize(int w, int h) noexcept {
    width = w;
    height = h;
}

void Application::Quit() noexcept {
    mQuit = true;
}