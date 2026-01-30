#ifndef MEGENGINEPROJECT_MAT4_H
#define MEGENGINEPROJECT_MAT4_H

#include "MEGEngine/common.h"
#include "MEGEngine/math/vec3.h"

namespace MEGEngine {
    class ENGINE_API Mat4 {
    public:
        float m[16]{0}; // the raw data in the matrices

        Mat4();
        explicit Mat4(float diagonal);

        static Mat4 identity();

        static Mat4 translation(Mat4& m, const Vec3& t);
        static Mat4 scale(Mat4& m, const Vec3& s);
        static Mat4 rotationX(Mat4& m, float radians);
        static Mat4 rotationY(Mat4& m, float radians);
        static Mat4 rotationZ(Mat4& m, float radians);

        static Mat4 translation(const Vec3& t);
        static Mat4 scale(const Vec3& s);
        static Mat4 rotationX(float radians);
        static Mat4 rotationY(float radians);
        static Mat4 rotationZ(float radians);

        static Mat4 perspective(float fovDegrees, float aspect, float near, float far);
        static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);

        static Mat4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& up);
        Mat4 inverse() const;
        Mat4 transpose() const;

        Mat4 operator*(const Mat4& other) const;
        Vec3 transformPoint(const Vec3& v) const;
        Vec3 transformVector(const Vec3& v) const;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_MAT4_H