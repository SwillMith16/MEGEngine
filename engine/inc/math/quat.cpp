#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"
#include "GLM/gtx/quaternion.hpp"

#include "math/quat.h"
#include "math/mat4.h"
#include "math/vec3.h"

#include "math/glm_conversions.h"

namespace MEGEngine {
    Quat::Quat() : x(0), y(0), z(0), w(1) {}

    Quat::Quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Quat Quat::identity() {
        return {0, 0, 0, 1};
    }

    Quat Quat::fromAxisAngle(const Vec3& axis, float radians) {
        glm::vec3 a(axis.x, axis.y, axis.z);
        glm::quat q = glm::angleAxis(radians, glm::normalize(a));
        return {q.x, q.y, q.z, q.w};
    }

    Quat Quat::fromEuler(float pitch, float yaw, float roll)
    {
        glm::quat q = glm::quat(glm::vec3(pitch, yaw, roll));
        return {q.x, q.y, q.z, q.w};
    }

    Quat Quat::normalised() const {
        glm::quat q(w, x, y, z);
        q = glm::normalize(q);
        return {q.x, q.y, q.z, q.w};
    }

    Quat Quat::inverse() const {
        glm::quat q(w, x, y, z);
        q = glm::inverse(q);
        return {q.x, q.y, q.z, q.w};
    }

    Mat4 Quat::toMatrix() const {
        glm::quat q(w, x, y, z);
        glm::mat4 m = glm::toMat4(q);
        return Private::fromGlmMat4(m);
    }

    Vec3 Quat::rotate(const Vec3& vec) const {
        glm::quat q(w, x, y, z);
        glm::vec3 r = q * glm::vec3(vec.x, vec.y, vec.z);

        return {r.x, r.y, r.z};
    }

    Quat Quat::operator*(const Quat& rhs) const {
        glm::quat a(w, x, y, z);
        glm::quat b(rhs.w, rhs.x, rhs.y, rhs.z);

        glm::quat r = a * b;

        return {r.x, r.y, r.z, r.w};
    }
} // MEGEngine