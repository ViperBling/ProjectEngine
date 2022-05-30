add_subdirectory(Programs)
add_subdirectory(Framework)

set(SourcesPath ${PROJECT_SOURCE_DIR}/Sources)

IF(${WIN32})
    set(PlatformOnlySources
            ${SourcesPath}/Framework/Common/Application/WindowsApplication.cpp

            ${SourcesPath}/Framework/RHI/D3D11/GraphicsManagerD3D11.cpp
            ${SourcesPath}/Framework/RHI/D3D11/VertexBufferD3D11.cpp
            ${SourcesPath}/Framework/RHI/D3D11/ShaderD3D11.cpp
            ${SourcesPath}/Framework/RHI/D3D11/IndexBufferD3D11.cpp
            ${SourcesPath}/Framework/RHI/D3D11/RenderMeshD3D11.cpp
            )
ELSEIF(${UNIX})
    IF(${APPLE})
    ELSE(${APPLE})
    ENDIF(${APPLE})
ENDIF(${WIN32})


add_library(ProjectEngineLib
        ${SourcesPath}/Framework/Common/Memory/Allocator.cpp
        ${SourcesPath}/Framework/Common/Memory/MemoryManager.cpp
        ${SourcesPath}/Framework/Common/Application/Application.cpp

        ${SourcesPath}/Framework/Common/IO/Keyboard.cpp
        ${SourcesPath}/Framework/Common/IO/Mouse.cpp

        ${SourcesPath}/Framework/Common/Object/Entity.cpp
        ${SourcesPath}/Framework/Common/Object/World.cpp

        ${SourcesPath}/Framework/Common/Object/Components/TransformComponent.cpp
        ${SourcesPath}/Framework/Common/Object/Components/MeshRenderComponent.cpp
        ${SourcesPath}/Framework/Common/Object/Components/CameraComponent.cpp

        ${SourcesPath}/Framework/Common/Object/System/MeshRenderSystem.cpp
        ${SourcesPath}/Framework/Common/Object/System/CameraSystem.cpp
        ${SourcesPath}/Framework/Common/Object/System/RenderDebugSystem.cpp

        ${SourcesPath}/Framework/Common/Utils/TimeManager.cpp

        ${SourcesPath}/Framework/RHI/RenderObject.cpp
        ${SourcesPath}/Framework/RHI/RenderMesh.cpp
        ${SourcesPath}/Framework/RHI/VertexBuffer.cpp
        ${SourcesPath}/Framework/RHI/Shader.cpp
        ${SourcesPath}/Framework/RHI/IndexBuffer.cpp
        ${SourcesPath}/Framework/RHI/Material.cpp

        ${PlatformOnlySources}
        )

IF(${WIN32})
    target_link_libraries(ProjectEngineLib user32 d3d11 d3dcompiler dxgi)
    target_link_libraries(ProjectEngineLib ${ASSIMP_LIBRARY} ${IRRXML_LIBRARY} ${ZLIB_LIBRARY})
ELSEIF(${UNIX})
    IF(${APPLE})
    ELSE(${APPLE})
    ENDIF(${APPLE})
ENDIF(${WIN32})

target_link_libraries(ProjectEngineLib ${XG_LIBRARY})
__add_xg_platform_dependencies(ProjectEngineLib)