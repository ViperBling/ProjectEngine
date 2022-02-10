#pragma once

#define PROJECTENGINE_ARCH_UNKNOWN      "unknown"
#define PROJECTENGINE_ARCH_PCC          "pcc"
#define PROJECTENGINE_ARCH_PCC64        "pcc64"
#define PROJECTENGINE_ARCH_i386         "i386"
#define PROJECTENGINE_ARCH_x86_64       "x86_64"

#if defined(arch_ppc)
    #define PROJECTENGINE_ARCH PROJECTENGINE_ARCH_PCC
#elif defined(arch_ppc64)
    #define PROJECTENGINE_ARCH PROJECTENGINE_ARCH_PCC64
#elif defined(arch_i386)
    #define PROJECTENGINE_ARCH PROJECTENGINE_ARCH_i386
#elif defined(arch_x86_64)
    #define PROJECTENGINE_ARCH PROJECTENGINE_ARCH_x86_64
#else
    #define PROJECTENGINE_ARCH PROJECTENGINE_ARCH_UNKNOWN
#endif
