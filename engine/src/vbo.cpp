//
// Created by Will on 05/12/2025.
//

#include "vbo.h"

// Constructor generates a vertex buffer object, binds it and links the vertices
// TODO: Return VBO constructor to how it was
VBO::VBO(std::vector<Vertex>& vertices) {
    glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::del() {
    glDeleteBuffers(1, &ID);
}