if( CMAKE_BUILD_TYPE STREQUAL "Release" )
    find_library(XG_LIBRARY xg PATHS ${PROJECT_SOURCE_DIR}/External/CrossGuid/Windows/Release_x64/lib)
    include_directories("${PROJECT_SOURCE_DIR}/External/CrossGuid/Windows/Release_x64/include")

    find_library(ASSIMP_LIBRARY assimp-vc141-mt PATHS ${PROJECT_SOURCE_DIR}/External/Assimp/Windows/Release_x64/lib)
    find_library(IRRXML_LIBRARY IrrXML PATHS ${PROJECT_SOURCE_DIR}/External/Assimp/Windows/Release_x64/lib)
    find_library(ZLIB_LIBRARY zlibstatic PATHS ${PROJECT_SOURCE_DIR}/External/Assimp/Windows/Release_x64/lib)
    include_directories("${PROJECT_SOURCE_DIR}/External/Assimp/Windows/Release_x64/include")
    include_directories("${PROJECT_SOURCE_DIR}/External/Boost/include")

    include_directories("${PROJECT_SOURCE_DIR}/External/Imgui")

else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    find_library(XG_LIBRARY xg PATHS ${PROJECT_SOURCE_DIR}/External/CrossGuid/Windows/Debug_x64/lib)
    include_directories("${PROJECT_SOURCE_DIR}/External/CrossGuid/Windows/Debug_x64/include")

    find_library(ASSIMP_LIBRARY assimp-vc141-mtd PATHS ${PROJECT_SOURCE_DIR}/External/Assimp/Windows/Debug_x64/lib)
    find_library(IRRXML_LIBRARY IrrXML PATHS ${PROJECT_SOURCE_DIR}/External/Assimp/Windows/Debug_x64/lib)
    find_library(ZLIB_LIBRARY zlibstatic PATHS ${PROJECT_SOURCE_DIR}/External/Assimp/Windows/Debug_x64/lib)
    include_directories("${PROJECT_SOURCE_DIR}/External/Assimp/Windows/Debug_x64/include")
    include_directories("${PROJECT_SOURCE_DIR}/External/Boost/include")

    include_directories("${PROJECT_SOURCE_DIR}/External/Imgui")

endif( CMAKE_BUILD_TYPE STREQUAL "Release")

MESSAGE( STATUS "CrossGuid lib found: " ${XG_LIBRARY})
MESSAGE( STATUS "ASSIMP_LIBRARY found: " ${ASSIMP_LIBRARY})
MESSAGE( STATUS "IRRXML_LIBRARY found: " ${IRRXML_LIBRARY})
MESSAGE( STATUS "ZLIB_LIBRARY found: " ${ZLIB_LIBRARY})