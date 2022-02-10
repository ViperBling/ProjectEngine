add_subdirectory(Programs)
add_subdirectory(Framework)

set(SourcesPath ${PROJECT_SOURCE_DIR}/Sources)

IF(${WIN32})
    set(PlatformOnlySources
            ${SourcesPath}/Framework/Common/Application/WindowsApplication.cpp
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
        ${PlatformOnlySources}
        )
