cmake_minimum_required(VERSION 4.0)

set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/libraries")

#find_package(OpenGL REQUIRED)

include_directories(Game
        inc
        ${LIB_PATH}/include
        ${PROJECT_SOURCE_DIR}/engine/inc
        ${PROJECT_SOURCE_DIR}/engine/ext/libraries/include
)

# App executable
add_executable(Game
        src/main.cpp
)

target_link_libraries(Game MEGEngine)

target_compile_definitions(Game PRIVATE $<$<CONFIG:Debug>:DEBUG>)

add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different                   # executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/debug/engine/libMEGEngine.dll"     # <-- in-file
        $<TARGET_FILE_DIR:Game>)                                        # <-- out-file path
