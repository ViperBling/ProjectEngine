#pragma once

#include "Platform.h"
#include "BuildType.h"

#if defined(PROJECTENGINE_WINDOWS)

    #include <crtdbg.h>
    #define PROJECTENGINE_ASSERT_IMPL(EXPR)     _ASSERTE(EXPR)

#elif defined(PROJECTENGINE_MACOS)

    #include <assert.h>
    #define PROJECTENGINE_ASSERT_IMPL(EXPR)     assert(EXPR)

#else
#endif

#if defined(PROJECTENGINE_DEBUG)
    #define PROJECTENGINE_ASSERT(EXPR)      PROJECTENGINE_ASSERT_IMPL(EXPR)

#elif defined(PROJECTENGINE_RELEASE)
    #define PROJECTENGINE_ASSERT(EXPR)      ((void)0)
#else
#endif