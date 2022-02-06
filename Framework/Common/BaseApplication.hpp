#pragma once

#include "IApplication.hpp"

namespace ProjectEngine
{
    class BaseApplication : implements IApplication
    {
    public:
        BaseApplication(GfxConfiguration& cfg);
        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

        virtual bool IsQuit();

        inline GfxConfiguration& GetConfiguration() { return m_Config; };
    
    protected:
        // Flag if need quit the main loop of the application
        static bool m_bQuit;
        GfxConfiguration m_Config;

    private:
        // hide the default construct to enforce a configuration
        BaseApplication(){};
    };
} // namespace ProjectEngine
