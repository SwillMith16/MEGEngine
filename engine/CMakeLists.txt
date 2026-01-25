cmake_minimum_required(VERSION 4.2)

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
        src/entity.cpp
        inc/entity.h
        inc/common.h
        inc/vertex.h
        inc/math/vec2.h
        inc/math/vec2.cpp
        inc/math/vec3.h
        inc/math/vec3.cpp
        inc/math/glm_conversions.h
        inc/math/mat4.cpp
        inc/math/mat4.h
        inc/shader_priv.h
        inc/math/quat.cpp
        inc/math/quat.h
        inc/math/vec4.cpp
        inc/math/vec4.h
        inc/utils/log.h
        inc/utils/log.cpp
        src/material.cpp
        inc/material.h
        src/mesh_renderer.cpp
        inc/mesh_renderer.h
        src/model_loader.cpp
        inc/model_loader.h
        src/transform.cpp
        inc/transform.h
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
        STB_IMAGE_IMPLEMENTATION
)

target_compile_options(MEGEngine
        PRIVATE -fPIC
)

if (UNIX)
    target_compile_options(MEGEngine
            PRIVATE -fvisibility=hidden
    )
endif ()


