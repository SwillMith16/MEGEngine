#ifndef MEGENGINE_VEC4_H
#define MEGENGINE_VEC4_H

namespace MEGEngine {
    class Vec4 {
    public:
        // Member vars
        float x, y, z, w;

        // Constructors
        constexpr Vec4() : x(0), y(0), z(0), w(0) {}
        constexpr Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        // Operators
        Vec4 operator+ (const Vec4 &v) const;
        Vec4 operator- (const Vec4 &v) const;
        Vec4 operator- () const;
        Vec4 operator* (float scalar) const;

        Vec4 operator+= (const Vec4 &v);
        Vec4 operator-= (const Vec4 &v);
        Vec4 operator*= (float scalar);

        // utility functions
        float length() const;
        Vec4 normalized() const;
        static float dot(const Vec4 &a, const Vec4 &b);
    };

    Vec4 operator* (float scalar, const Vec4 &v);
} // MEGEngine

#endif //MEGENGINE_VEC4_H