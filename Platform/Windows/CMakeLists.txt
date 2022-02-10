add_library(WindowsApplication WindowsApplication.cpp)

add_executable(ProjectEngine_D3D12 D3D12Application.cpp)
target_link_libraries(ProjectEngine_D3D12 WindowsApplication Common D3DRHI d3d12 dxgi d3dcompiler)

find_package(OpenGL REQUIRED)

add_executable(ProjectEngine_OpenGL
    OpenGLApplication.cpp
    ${PROJECT_SOURCE_DIR}/External/src/glad/src/glad_wgl.c
    )
target_link_libraries(ProjectEngine_OpenGL WindowsApplication Common OpenGLRHI ${OPENGL_LIBRARIES})
target_include_directories(ProjectEngine_OpenGL PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")