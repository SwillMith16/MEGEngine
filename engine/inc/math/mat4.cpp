#include "mat4.h"
#include "glm_conversions.h"
#include "GLM/gtx/transform.hpp"

namespace MEGEngine {
    Mat4::Mat4() {
        *this = identity();
    }

    Mat4::Mat4(float diagonal) {
        // set all data in matrix to 0
        for (float& i : m)
            i = 0.0f;

        m[0] = m[5] = m[10] = m[15] = diagonal;
    }

    Mat4 Mat4::identity() {
        return Mat4(1.0f);
    }



    Mat4 Mat4::translation(const Vec3& t) {
        return Private::fromGlmMat4(glm::translate(glm::mat4(1.0f), Private::toGlmVec3(t)));
    }

    Mat4 Mat4::scale(const Vec3& s) {
        return Private::fromGlmMat4(glm::scale(glm::mat4(1.0f), Private::toGlmVec3(s)));
    }



    Mat4 Mat4::rotationX(float radians) {
        return Private::fromGlmMat4(glm::rotate(glm::mat4(1.0f), radians, Private::toGlmVec3({1, 0, 0})));
    }

    Mat4 Mat4::rotationY(float radians) {
        return Private::fromGlmMat4(glm::rotate(glm::mat4(1.0f), radians, Private::toGlmVec3({0, 1, 0})));
    }

    Mat4 Mat4::rotationZ(float radians) {
        return Private::fromGlmMat4(glm::rotate(glm::mat4(1.0f), radians, Private::toGlmVec3({0, 0, 1})));
    }


    Mat4 Mat4::perspective(float fovDegrees, float aspect, float near, float far) {
        return Private::fromGlmMat4(glm::perspective(glm::radians(fovDegrees), aspect, near, far));
    }

    Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
        return Private::fromGlmMat4(glm::ortho(left, right, bottom, top, near, far));
    }


    Mat4 Mat4::inverse() const {
        return Private::fromGlmMat4(glm::inverse(Private::toGlmMat4(*this)));
    }

    Mat4 Mat4::transpose() const {
        return Private::fromGlmMat4(glm::transpose(Private::toGlmMat4(*this)));
    }

    Mat4 Mat4::lookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
        return Private::fromGlmMat4(
            glm::lookAt(
                Private::toGlmVec3(eye),
                Private::toGlmVec3(target),
                Private::toGlmVec3(up)
            )
        );
    }


    Mat4 Mat4::operator*(const Mat4& other) const
    {
        return Private::fromGlmMat4(Private::toGlmMat4(*this) * Private::toGlmMat4(other));
    }

    Vec3 Mat4::transformPoint(const Vec3& v) const
    {
        glm::vec4 r = Private::toGlmMat4(*this) * glm::vec4(v.x, v.y, v.z, 1.0f);
        return {r.x, r.y, r.z};
    }

    Vec3 Mat4::transformVector(const Vec3& v) const
    {
        glm::vec4 r = Private::toGlmMat4(*this) * glm::vec4(v.x, v.y, v.z, 0.0f);
        return {r.x, r.y, r.z};
    }
} // MEGEngine