#ifndef MEGENGINEPROJECT_VERTEX_H
#define MEGENGINEPROJECT_VERTEX_H

#include "MEGEngine/common.h"

#include "MEGEngine/math/vec3.h"
#include "MEGEngine/math/vec2.h"

namespace MEGEngine {
    class ENGINE_API Vertex {
    public:
        Vertex(Vec3 position, Vec3 normal, Vec3 colour, Vec2 texUV) : position(position), normal(normal), colour(colour), texUV(texUV) {};
        Vec3 position;
        Vec3 normal;
        Vec3 colour;
        Vec2 texUV;
    };
}

#endif //MEGENGINEPROJECT_VERTEX_H