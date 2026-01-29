#ifndef MEGENGINEPROJECT_PRIMITIVE_SHAPES_H
#define MEGENGINEPROJECT_PRIMITIVE_SHAPES_H

#include <vector>

#include "common.h"

#include "vertex.h"

namespace MEGEngine {
    class ENGINE_API Cube {
    public:
    	static std::vector<Vertex>& vertices() { return _vertices; };
    	static std::vector<unsigned int>& indices() { return _indices; };

    private:
    	static std::vector<Vertex> _vertices;
    	static std::vector<unsigned int> _indices;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_PRIMITIVE_SHAPES_H