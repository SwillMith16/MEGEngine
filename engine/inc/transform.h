#ifndef MEGENGINEPROJECT_TRANSFORM_H
#define MEGENGINEPROJECT_TRANSFORM_H

#include "common.h"

#include "math/quat.h"
#include "math/mat4.h"
#include "math/vec3.h"

namespace MEGEngine {
    class ENGINE_API Transform {
    public:
        Transform();

        void setPosition(const Vec3& position);
        void setRotation(const Quat& rotation);
        void setScale(const Vec3& scale);
        void setScale(float scale);

        Vec3 position() const;
        Quat rotation() const;
        Vec3 scale() const;

        Mat4 modelMatrix() const;

    private:
        Vec3 _position = Vec3(0, 0, 0);
        Quat _rotation = Quat::identity();
        Vec3 _scale = Vec3(1, 1, 1);
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_TRANSFORM_H