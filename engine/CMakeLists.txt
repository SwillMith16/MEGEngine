cmake_minimum_required(VERSION 4.2)

add_library(MEGEngine SHARED
        inc/MEGEngine/application.h
        src/application.cpp
        inc/MEGEngine/shader.h
        src/shader.cpp
        src/vao.cpp
        inc/MEGEngine/vao.h
        src/vbo.cpp
        inc/MEGEngine/vbo.h
        src/ebo.cpp
        inc/MEGEngine/ebo.h
        src/texture.cpp
        inc/MEGEngine/texture.h
        src/camera.cpp
        inc/MEGEngine/camera.h
        src/settings.cpp
        inc/MEGEngine/settings.h
        src/mesh.cpp
        inc/MEGEngine/mesh.h
        src/entity.cpp
        inc/MEGEngine/entity.h
        inc/MEGEngine/common.h
        inc/MEGEngine/vertex.h
        inc/MEGEngine/math/vec2.h
        inc/MEGEngine/math/vec2.cpp
        inc/MEGEngine/math/vec3.h
        inc/MEGEngine/math/vec3.cpp
        inc/MEGEngine/math/glm_conversions.h
        inc/MEGEngine/math/mat4.cpp
        inc/MEGEngine/math/mat4.h
        inc/MEGEngine/math/quat.cpp
        inc/MEGEngine/math/quat.h
        inc/MEGEngine/math/vec4.cpp
        inc/MEGEngine/math/vec4.h
        inc/MEGEngine/utils/log.h
        inc/MEGEngine/utils/log.cpp
        src/material.cpp
        inc/MEGEngine/material.h
        src/mesh_renderer.cpp
        inc/MEGEngine/mesh_renderer.h
        src/model_loader.cpp
        inc/MEGEngine/model_loader.h
        src/transform.cpp
        inc/MEGEngine/transform.h
        src/primitive_shapes.cpp
        inc/MEGEngine/primitive_shapes.h
        src/shader_manager.cpp
        inc/MEGEngine/shader_manager.h
        src/scene.cpp
        inc/MEGEngine/scene.h
        src/window.cpp
        inc/MEGEngine/window.h
        src/renderer.cpp
        inc/MEGEngine/renderer.h
        inc/MEGEngine.h
        inc/MEGEngine/Math.h
        src/event_manager.cpp
        inc/MEGEngine/event_manager.h
        src/events.cpp
        inc/MEGEngine/events.h
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


