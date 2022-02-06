add_executable(ProjectEngine_D3D12 WindowsApplication.cpp D3D12Application.cpp)
target_link_libraries(ProjectEngine_D3D12 Common D3DRHI d3d12 dxgi d3dcompiler)

add_executable(ProjectEngine_OpenGL
    WindowsApplication.cpp 
    OpenGLApplication.cpp
    ${PROJECT_SOURCE_DIR}/External/GL/src/glad_wgl.c
    )
target_link_libraries(ProjectEngine_OpenGL Common OpenGLRHI opengl32)
target_include_directories(ProjectEngine_OpenGL PRIVATE "${PROJECT_SOURCE_DIR}/External/GL/include")