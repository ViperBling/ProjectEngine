#include <iostream>
#include <string>
#include "AssetLoader.hpp"
#include "MemoryManager.hpp"

using namespace std;
using namespace ProjectEngine;

namespace ProjectEngine
{
    MemoryManager* g_pMemoryManager = new MemoryManager();
}

int main(int, char**)
{
    g_pMemoryManager->Initialize();

    AssetLoader assetLoader;
    string shader_pgm = assetLoader.SyncOpenAndReadTextFileToString("Shaders/copy_vs.hlsl");

    cout << shader_pgm;

    g_pMemoryManager->Finalize();

    delete g_pMemoryManager;

    return 0;
}