#pragma once

#include "Framework/Interface/IModule.h"

namespace ProjectEngine
{
    class IRenderResource{};

    enum VertexFormat
    {
        None = 0,
        VF_P3F,
        VF_T2F,
        VF_N3F,
        VF_C4B,
    };

    class IVertexBuffer : public IRenderResource {};

    class IMesh : public IRenderResource{};
}