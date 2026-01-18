cmake_minimum_required(VERSION 4.2)

find_library(GLFW
        NAMES libglfw3.a libglfw3.so
        PATHS /usr/local/lib64/GLFW/
)
find_library(GLAD
        NAMES libGLAD.a libGLAD.so
        PATHS /usr/local/lib64/GLAD/
)

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

target_include_directories(MEGEngine
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ext/
)

# GLFW and GLAD libraries
target_link_libraries(MEGEngine PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ext/GLFW/libglfw3.a
        ${CMAKE_CURRENT_SOURCE_DIR}/ext/GLAD/libGLADstatic.a
        ${CMAKE_CURRENT_SOURCE_DIR}/ext/GLM/libglm.a
)

target_compile_definitions(MEGEngine PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        ENGINE_BUILD
        GLM_ENABLE_EXPERIMENTAL
)

target_compile_options(MEGEngine PRIVATE -fPIC)


