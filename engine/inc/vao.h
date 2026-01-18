//
// Created by Will on 05/12/2025.
//

#ifndef VAO_H
#define VAO_H

#include "GLAD/glad.h"
#include "vbo.h"

class VAO {
public:
    GLuint ID;
    VAO();

    void linkAttrib(MEGEngine::VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void bind();
    void unbind();
    void del();

    bool isActive();

private:
    bool active = false;
};


#endif //VAO_H