add_executable(ProjectEngine ProjectEngine.cpp)
target_link_libraries(ProjectEngine ProjectEngineLib)

install( TARGETS ProjectEngine DESTINATION "${PROJECT_SOURCE_DIR}/Binary/${TARGET_ARCH}/${CMAKE_BUILD_TYPE}")