#ifndef MEGENGINEPROJECT_QUAT_H
#define MEGENGINEPROJECT_QUAT_H

namespace MEGEngine {
    class Quat {
    public:
        float x, y, z, w;

        Quat();
        Quat(float x, float y, float z, float w);

        static Quat identity();
        static Quat fromAxisAngle(const class Vec3& axis, float radians);
        static Quat fromEuler(float pitch, float yaw, float roll);

        Quat normalised() const;
        Quat inverse() const;

        class Mat4 toMatrix() const;

        class Vec3 rotate(const class Vec3& v) const;

        Quat operator*(const Quat& rhs) const;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_QUAT_H