#include "BaseApplication.hpp"

namespace ProjectEngine
{
    GfxConfiguration config;
    BaseApplication g_App(config);
    IApplication* g_pApp = &g_App;
}