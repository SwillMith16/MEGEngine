#include "math/vec4.h"
#include "math/glm_conversions.h"

#include "GLM/glm.hpp"

namespace MEGEngine {

    Vec4 Vec4::operator+(const Vec4 &v) const {
        // convert this and other vec to glm, perform addition and convert back to return Vec4
        return Private::fromGlmVec4(Private::toGlmVec4(*this) + Private::toGlmVec4(v));
    }

    Vec4 Vec4::operator-(const Vec4 &v) const {
        return Private::fromGlmVec4(Private::toGlmVec4(*this) - Private::toGlmVec4(v));
    }

    Vec4 Vec4::operator-() const {
        return (*this * -1);
    }

    Vec4 Vec4::operator*(float scalar) const {
        return Private::fromGlmVec4(Private::toGlmVec4(*this) * scalar);
    }

    Vec4 Vec4::operator+=(const Vec4 &v) {
        *this = *this + v;
        return *this;
    }

    Vec4 Vec4::operator-=(const Vec4 &v) {
        *this = *this - v;
        return *this;
    }

    Vec4 Vec4::operator*=(float scalar) {
        *this = *this * scalar;
        return *this;
    }


    float Vec4::length() const {
        return glm::length(Private::toGlmVec4(*this));
    }

    Vec4 Vec4::normalized() const {
        return Private::fromGlmVec4(glm::normalize(Private::toGlmVec4(*this)));
    }

    float Vec4::dot(const Vec4 &a, const Vec4& b) {
        return glm::dot(Private::toGlmVec4(a), Private::toGlmVec4(b));
    }

    Vec4 operator*(float scalar, const Vec4 &v) {
        return Private::fromGlmVec4(scalar * Private::toGlmVec4(v));
    }
} // MEGEngine