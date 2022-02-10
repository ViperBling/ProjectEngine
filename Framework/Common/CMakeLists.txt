add_library(Common
    Allocator.cpp
    AssetLoader.cpp
    BaseApplication.cpp
    GraphicsManager.cpp
    Image.cpp
    MemoryManager.cpp
    SceneManager.cpp
    ProjectEngine.cpp
    )

target_link_libraries(Common GeomMath)

find_library(XG_LIBRARY xg PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
find_library(OPENDDL_LIBRARY OpenDDL PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
find_library(OPENGEX_LIBRARY OpenGEX PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})

target_link_libraries(Common ${XG_LIBRARY})

include(PlatformDependencies)