#ifndef MEGENGINE_VBO_H
#define MEGENGINE_VBO_H

#include <vector>

#include "MEGEngine/vertex.h"

namespace MEGEngine {
    class VBO {
    public:
        unsigned int ID;
        VBO(const std::vector<Vertex>& vertices);

        void bind();
        void unbind();
        void del();
    };
}



#endif