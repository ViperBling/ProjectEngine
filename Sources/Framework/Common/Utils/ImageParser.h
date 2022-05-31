#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <string>

#include "Framework/Common/Utils/stb_image.h"

namespace ProjectEngine
{
    class ImageParser
    {
    public:
        static unsigned char* Parser(
            const std::string& file, int* width, int* height,
            int* channels, int desiredChannels
            )
        {
            auto data = stbi_load(file.c_str(), width, height, channels, desiredChannels);
            return data;
        }
    };
}