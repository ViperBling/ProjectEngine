#include "Application.h"

using namespace ProjectEngine;

int Application::Initialize() noexcept {
    mQuit = false;
    mMemoryManager = nullptr;
    mGraphicsManager = nullptr;
    mWorld = nullptr;
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

void Application::Quit() noexcept {
    mQuit = true;
}