#ifndef MEGENGINEPROJECT_COLOUR_H
#define MEGENGINEPROJECT_COLOUR_H

#include "MEGEngine/common.h"

namespace MEGEngine {
    class ENGINE_API Colour {
    public:
        float r, g, b, a;

        // Constructors
        constexpr Colour() : r(0), g(0), b(0), a(0) {}
        constexpr Colour(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_COLOUR_H