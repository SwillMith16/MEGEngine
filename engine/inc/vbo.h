//
// Created by Will on 05/12/2025.
//

#ifndef VBO_H
#define VBO_H

#include "GLAD/glad.h"
#include "GLM/glm.hpp"
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 colour;
	glm::vec2 texUV;
};

class VBO {
public:
    GLuint ID;
    VBO(std::vector<Vertex>& vertices);

    void bind();
    void unbind();
    void del();
};


#endif //VBO_H