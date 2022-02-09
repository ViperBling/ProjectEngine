#pragma once
#include "GeomMath.hpp"
#include "IRuntimeModule.hpp"
#include "SceneNode.hpp"

namespace ProjectEngine
{
    class SceneManager : implements IRuntimeModule
    {
    public:
        virtual ~SceneManager();

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

    protected:
        SceneEmptyNode m_RootNode;
    };
}