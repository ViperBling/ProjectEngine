#include <iostream>
#include "EmptyApplication.hpp"

using namespace ProjectEngine;

int main(int argc, char** argv) 
{
    int ret;

    if ((ret = g_pApp->Initialize()) != 0) 
    {
        std::cout << "App Initialize failed, will exit now." << std::endl;
        return ret;
    }

    if ((ret = g_pMemoryManager->Initialize()) != 0) 
    {
        std::cout << "Memory Manager Initialize failed, will exit now." << std::endl;
        return ret;
    }

    if ((ret = g_pGraphicsManager->Initialize()) != 0) 
    {
        std::cout << "Graphics Manager Initialize failed, will exit now." << std::endl;
        return ret;
    }

    if ((ret = g_pAssetLoader->Initialize()) != 0) {
        std::cout << "Asset Loader Initialize failed, will exit now." << std::endl;
        return ret;
    }

    if ((ret = g_pSceneManager->Initialize()) != 0) {
        std::cout << "Scene Manager Initialize failed, will exit now." << std::endl;
        return ret;
    }

    while (!g_pApp->IsQuit())
    {
        g_pApp->Tick();
        g_pMemoryManager->Tick();
        g_pGraphicsManager->Tick();
        g_pAssetLoader->Tick();
        g_pSceneManager->Tick();
    }

    g_pSceneManager->Finalize();
    g_pAssetLoader->Finalize();
    g_pGraphicsManager->Finalize();
    g_pMemoryManager->Finalize();
    g_pApp->Finalize();

    return 0;
}