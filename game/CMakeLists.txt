cmake_minimum_required(VERSION 4.2)

set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/libraries")

# App executable
add_executable(Game
        src/main.cpp
)

target_include_directories(Game PRIVATE
        inc
        ${LIB_PATH}/include
        ${PROJECT_SOURCE_DIR}/engine/inc
)

target_link_libraries(Game MEGEngine)

target_compile_definitions(Game PRIVATE $<$<CONFIG:Debug>:DEBUG>)

if (WIN32)
    set(ENGINE_LIB_FILE libMEGEngine.dll)
else(UNIX)
    set(ENGINE_LIB_FILE libMEGEngine.so)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_FOLDER "debug")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(BUILD_FOLDER "release")
endif ()

add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different                   # executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/${BUILD_FOLDER}/engine/${ENGINE_LIB_FILE}"     # <-- in-file
        $<TARGET_FILE_DIR:Game>)                                        # <-- out-file path
