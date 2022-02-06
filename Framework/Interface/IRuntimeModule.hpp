#pragma once

#include "Interface.hpp"

namespace ProjectEngine 
{
    Interface IRuntimeModule {
    public:
        virtual ~IRuntimeModule() {};
        // 纯虚函数
        virtual int Initialize() = 0;
        virtual void Finalize() = 0;

        virtual void Tick() = 0;
    };
}