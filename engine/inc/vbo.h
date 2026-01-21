#ifndef MEGENGINE_VBO_H
#define MEGENGINE_VBO_H

#include <vector>

#include "vertex.h"

namespace MEGEngine {
    class VBO {
    public:
        unsigned int ID;
        VBO(std::vector<Vertex>& vertices);

        void bind();
        void unbind();
        void del();
    };
}



#endif