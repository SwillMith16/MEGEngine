#include "MEGEngine/transform.h"

#include "MEGEngine/math/glm_conversions.h"

namespace MEGEngine {
    Transform::Transform() : _scale(1, 1, 1) {}

    // z flipped so positive is moving away same done when getting position vector
    void Transform::setPosition(const Vec3& position) {_position = Vec3(position.x, position.y, -position.z);}
    void Transform::setRotation(const Quat& rotation) {_rotation = rotation;}
    void Transform::setScale(const Vec3& scale) {_scale = scale;}
    void Transform::setScale(float scale) {_scale = Vec3(scale, scale, scale);}

    Vec3 Transform::position() const {return {_position.x, _position.y, -_position.z};}
    Quat Transform::rotation() const {return _rotation;}
    Vec3 Transform::scale() const {return _scale;}

    Mat4 Transform::modelMatrix() const {
        Mat4 m(1.0f);
        m = Mat4::translation(m, _position);
        m = Mat4::rotationX(m, glm::radians(_rotation.x));
        m = Mat4::rotationY(m, glm::radians(_rotation.y));
        m = Mat4::rotationZ(m, glm::radians(_rotation.z));
        m = Mat4::scale(m, _scale);

        return m;
    }
} // MEGEngine