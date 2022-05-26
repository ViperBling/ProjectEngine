add_executable(ProjectEngine ProjectEngine.cpp)
target_link_libraries(ProjectEngine ProjectEngineLib)

install(TARGETS ProjectEngine DESTINATION "${PROJECT_SOURCE_DIR}/Binary/${TARGET_ARCH}/${CMAKE_BUILD_TYPE}")

install(DIRECTORY "${PROJECT_SOURCE_DIR}/Asset" DESTINATION "${PROJECT_SOURCE_DIR}/Binary/${TARGET_ARCH}/${CMAKE_BUILD_TYPE}")


add_custom_command(TARGET ProjectEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Asset/Scene
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Asset/Scene)