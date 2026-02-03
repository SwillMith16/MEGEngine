#include "MEGEngine/transform.h"

#include "MEGEngine/math/glm_conversions.h"

namespace MEGEngine {
    Transform::Transform() : _scale(1, 1, 1) {}

    // z flipped so positive is moving away same done when getting position vector
    void Transform::setPosition(const Vec3& position) {_position = position;}
    void Transform::setOrientation(const Quat& orientation) {_orientation = orientation;}
    void Transform::setScale(const Vec3& scale) {_scale = scale;}
    void Transform::setScale(float scale) {_scale = Vec3(scale, scale, scale);}

    Vec3 Transform::position() const {return _position;}
    Quat Transform::orientation() const {return _orientation;}
    Vec3 Transform::scale() const {return _scale;}

    Mat4 Transform::modelMatrix() const {
        Mat4 trans = Mat4::translation(_position);
        Mat4 rot = _orientation.toMatrix();
        Mat4 sca = Mat4::scale(_scale);

        return trans * rot * sca;
    }
} // MEGEngine