#ifndef VAO_H
#define VAO_H

#include "MEGEngine/vbo.h"

namespace MEGEngine {
    class VAO {
    public:
        unsigned int ID;
        VAO();

        void linkAttrib(VBO& VBO, unsigned int layout, int numComponents, int stride, void* offset);
        void bind();
        void unbind();
        void del();

        bool isActive();

    private:
        bool active = false;
    };
}

#endif //VAO_H