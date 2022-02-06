#include "BaseApplication.hpp"
#include <iostream>

using namespace ProjectEngine;

bool BaseApplication::m_bQuit = false;

BaseApplication::BaseApplication(GfxConfiguration& cfg) : m_Config(cfg)
{
    
}


int BaseApplication::Initialize()
{
    int result = 0;

    std::wcout << m_Config;
    return result;
}

void BaseApplication::Finalize()
{

}

void BaseApplication::Tick()
{

}

bool BaseApplication::IsQuit()
{
    return m_bQuit;
}