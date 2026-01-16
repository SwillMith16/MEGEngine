cmake_minimum_required(VERSION 4.0)

set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/libraries")

include_directories(MEGEngine
        inc
        ${LIB_PATH}/include
)

# App executable
add_library(MEGEngine SHARED
        inc/application.h
        src/application.cpp
        inc/shader.h
        src/shader.cpp
        src/vao.cpp
        inc/vao.h
        src/vbo.cpp
        inc/vbo.h
        src/ebo.cpp
        inc/ebo.h
        src/stb.cpp
        src/texture.cpp
        inc/texture.h
        src/camera.cpp
        inc/camera.h
        src/timer.cpp
        inc/timer.h
        src/settings.cpp
        inc/settings.h
        src/mesh.cpp
        inc/mesh.h
        src/model.cpp
        inc/model.h
        src/app.cpp
        inc/app.h
        inc/common.h
)

# GLFW and GLAD libraries
target_link_libraries(MEGEngine PRIVATE
        ${LIB_PATH}/libglfw3.a
        ${LIB_PATH}/libglad.a
)

target_compile_definitions(MEGEngine PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        ENGINE_BUILD
)


