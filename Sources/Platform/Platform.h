#pragma once

#define PROJECTENGINE_PLATFORM_UNKNOWN				"unknown"
#define PROJECTENGINE_PLATFORM_WINDOWS				"windows"
#define PROJECTENGINE_PLATFORM_MACOS				"macos"

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
    #define PROJECTENGINE_PLATFORM	PROJECTENGINE_PLATFORM_WINDOWS
    #define PROJECTENGINE_WINDOWS

#elif defined(__APPLE__)
    #define PROJECTENGINE_PLATFORM	PROJECTENGINE_PLATFORM_MACOS
	#define PROJECTENGINE_MACOS
#else
    #define PROJECTENGINE_PLATFORM	PROJECTENGINE_PLATFORM_UNKNOWN
    #define PROJECTENGINE_UNKNOWN
#endif

#if defined(PROJECTENGINE_WINDOWS)
    #include "Platform/Windows.h"
#elif defined(PROJECTENGINE_MACOS)
    #include "Platform/MacOS.h"
#else
#endif