#ifndef EBO_H
#define EBO_H

#include "GLAD/glad.h"
#include <vector>

class EBO {
public:
    GLuint ID;
    EBO(std::vector<GLuint>& indices);

    void bind();
    void unbind();
    void del();

};

#endif //EBO_H