//
// Created by Will on 05/12/2025.
//

#include "vao.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

// links a VBO to the VAO and assigns the vertex attributes
void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    VBO.bind();
    glEnableVertexAttribArray(layout);
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
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