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
