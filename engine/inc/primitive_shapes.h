#ifndef MEGENGINEPROJECT_PRIMITIVE_SHAPES_H
#define MEGENGINEPROJECT_PRIMITIVE_SHAPES_H

#include <vector>

#include "common.h"

#include "vertex.h"

namespace MEGEngine {
    class Primitive {
    public:
        std::vector<Vertex>& vertices();
        std::vector<unsigned int>& indices();
    protected:
        Primitive() = default;

        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
    };

    class ENGINE_API Cube : public Primitive {
    public:
        Cube();
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_PRIMITIVE_SHAPES_H