#pragma once

#include "Interface.hpp"

namespace ProjectEngine 
{

    Interface IRuntimeModule {
    public:
        virtual ~IRuntimeModule() {};
        // 定义纯虚函数，强制子类实现
        virtual int Initialize() = 0;
        virtual void Finalize() = 0;

        virtual void Tick() = 0;
    };
}