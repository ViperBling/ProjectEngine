cmake_minimum_required (VERSION 3.1)
project (ProjectEngine)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")
include(TargetArchDetect)

target_architecture(TARGET_ARCH)

if((TARGET_ARCH MATCHES "x86_64" OR TARGET_ARCH MATCHES "ia64") AND NOT OF_32BIT)
    set(ARCH_BIT 64)
else()
    set(ARCH_BIT 32)
endif()

include_directories("${PROJECT_SOURCE_DIR}/Framework/Common")
include_directories("${PROJECT_SOURCE_DIR}/Framework/GeomMath")
include_directories("${PROJECT_SOURCE_DIR}/Framework/Interface")
include_directories("${PROJECT_SOURCE_DIR}/Framework/Parser")
include_directories("${PROJECT_SOURCE_DIR}/RHI")
include_directories("${PROJECT_SOURCE_DIR}/")

IF(${UNIX})
    IF(${APPLE})
        set(PE_TARGET_PLATFORM "Darwin")
    ELSE(${LINUX})
        set(PE_TARGET_PLATFORM "Linux")
    ENDIF(${APPLE})
ELSEIF(${WIN32})
    set(PE_TARGET_PLATFORM "Windows")
ENDIF(${UNIX})

include_directories("${PROJECT_SOURCE_DIR}/Platform/${PE_TARGET_PLATFORM}")
set(PE_EXTERNAL_ROOT ${PROJECT_SOURCE_DIR}/External/${PE_TARGET_PLATFORM}/)
include_directories("${PE_EXTERNAL_ROOT}include")
set(PE_EXTERNAL_LIBRARY_PATH ${PE_EXTERNAL_ROOT}lib/)
find_library(XG_LIBRARY xg PATHS ${PE_EXTERNAL_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH)
find_library(OPENDDL_LIBRARY OpenDDL PATHS ${PE_EXTERNAL_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH)
find_library(OPENGEX_LIBRARY OpenGEX PATHS ${PE_EXTERNAL_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH)

include(CTest)
include(CheckCXXSourceCompiles)
include(PlatformDependencies)

#CHECK_CXX_SOURCE_COMPILES(
#        "#include <memory>
#
#int main(int argc, char** argv)
#{
#    std::unique_ptr<int> my_int = std::make_unique<int>();
#    *my_int = 0;
#    return *my_int;
#}
#"
#        HAVE_MAKE_UNIQUE)
#configure_file(CMake/config.h.in CMake/config.h)
add_subdirectory(Framework)
add_subdirectory(Platform)
add_subdirectory(RHI)
add_subdirectory(Test)