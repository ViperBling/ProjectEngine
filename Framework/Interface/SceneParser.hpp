#pragma once

#include <memory>
#include <string>
#include "Scene.hpp"

namespace ProjectEngine
{
    Interface SceneParser
    {
    public:
        virtual std::unique_ptr<Scene> Parse(const std::string& buf) = 0;
    };
};