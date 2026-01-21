#include "GLAD/glad.h"

#include "ebo.h"

namespace MEGEngine {
    // Constructor that generates an Element Buffer Object
    // TODO: Return EBO constructor to how it was
    EBO::EBO(std::vector<unsigned int>& indices) {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    // Binds the EBO
    void EBO::bind() { // bind the buffer using the already attached indices data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    // Unbinds the EBO
    void EBO::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    // Deletes the EBO
    void EBO::del() {
        glDeleteBuffers(1, &ID);
    }
}