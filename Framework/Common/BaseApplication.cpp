#include "BaseApplication.hpp"

int ProjectEngine::BaseApplication::Initialize()
{
    m_bQuit = false;
    return 0;
}

void ProjectEngine::BaseApplication::Finalize()
{

}

void ProjectEngine::BaseApplication::Tick()
{

}

bool ProjectEngine::BaseApplication::IsQuit()
{
    return m_bQuit;
}