IF(${WIN32})
    add_subdirectory(Windows)
ENDIF(${WIN32})


add_executable(TestMath TestMath.cpp)
add_test(NAME TestMath COMMAND TestMath)

add_executable(TestGuid TestGuid.cpp)
target_link_libraries(TestGuid ${XG_LIBRARY})
__add_xg_platform_dependencies(TestGuid)
add_test(NAME TestGuid COMMAND TestGuid)

add_executable(TestGMemoryManager TestGMemoryManager.cpp)
target_link_libraries(TestGMemoryManager ProjectEngineLib)
add_test(NAME TestGMemoryManager COMMAND TestGMemoryManager)


add_executable(TestAssimp TestAssimp.cpp)
target_link_libraries(TestAssimp ${ASSIMP_LIBRARY} ${IRRXML_LIBRARY} ${ZLIB_LIBRARY})
add_test(NAME TestAssimp COMMAND Test_Assimp)
add_custom_command(TARGET TestAssimp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Asset/Scene/aili_cycle.blend
        ${CMAKE_CURRENT_BINARY_DIR}/Asset/Scene/aili_cycle.blend)

add_custom_command(TARGET TestAssimp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Asset/Scene/aili_cycle.fbx
        ${CMAKE_CURRENT_BINARY_DIR}/Asset/Scene/aili_cycle.fbx)