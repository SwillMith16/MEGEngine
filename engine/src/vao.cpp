#include "GLAD/glad.h"

#include "MEGEngine/vao.h"

namespace MEGEngine {
    VAO::VAO() {
        glGenVertexArrays(1, &ID);
    }

    // links a VBO to the VAO and assigns the vertex attributes
    void VAO::linkAttrib(MEGEngine::VBO& VBO, unsigned int layout, int numComponents, int stride, void* offset) {
        VBO.bind();
        glEnableVertexAttribArray(layout);
        glVertexAttribPointer(layout, numComponents, GL_FLOAT, GL_FALSE, stride, offset);
        VBO.unbind();
    }

    void VAO::bind() {
        glBindVertexArray(ID);
        active = true;
    }

    void VAO::unbind() {
        glBindVertexArray(0);
        active = false;
    }

    void VAO::del() {
        glDeleteVertexArrays(1, &ID);
    }

    bool VAO::isActive() {
        return active;
    }
}