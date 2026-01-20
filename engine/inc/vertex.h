#ifndef MEGENGINEPROJECT_VERTEX_H
#define MEGENGINEPROJECT_VERTEX_H

#include "common.h"

#include "GLM/glm.hpp"

namespace MEGEngine {
    class ENGINE_API Vertex {
    public:
        Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 colour, glm::vec2 texUV) : position(position), normal(normal), colour(colour), texUV(texUV) {};
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 colour;
        glm::vec2 texUV;
    };
}

#endif //MEGENGINEPROJECT_VERTEX_H