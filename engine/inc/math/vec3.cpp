#include "math/vec3.h"
#include "math/glm_conversions.h"

#include "GLM/glm.hpp"

namespace MEGEngine {

	Vec3 Vec3::operator+(const Vec3 &v) const {
		// convert this and other vec to glm, perform addition and convert back to return Vec3
		return Private::fromGlmVec3(Private::toGlmVec3(*this) + Private::toGlmVec3(v));
	}

	Vec3 Vec3::operator-(const Vec3 &v) const {
		return Private::fromGlmVec3(Private::toGlmVec3(*this) - Private::toGlmVec3(v));
	}

	Vec3 Vec3::operator-() const {
		return (*this*-1);
	}

	Vec3 Vec3::operator*(float scalar) const {
		return Private::fromGlmVec3(Private::toGlmVec3(*this) * scalar);
	}

	Vec3 operator*(float scalar, const Vec3 &v) {
		return v * scalar;
	}

	Vec3 Vec3::operator+=(const Vec3 &v) {
		*this = *this + v;
		return *this;
	}

	Vec3 Vec3::operator-=(const Vec3 &v) {
		*this = *this - v;
		return *this;
	}

	Vec3 Vec3::operator*=(float scalar) {
		*this = *this * scalar;
		return *this;
	}


	float Vec3::length() const {
		return glm::length(Private::toGlmVec3(*this));
	}

	Vec3 Vec3::normalized() const {
		return Private::fromGlmVec3(glm::normalize(Private::toGlmVec3(*this)));
	}

	float Vec3::dot(const Vec3 &a, const Vec3& b) {
		return glm::dot(Private::toGlmVec3(a), Private::toGlmVec3(b));
	}

	Vec3 Vec3::cross(const Vec3 &a, const Vec3& b) {
		return Private::fromGlmVec3(glm::cross(Private::toGlmVec3(a), Private::toGlmVec3(b)));
	}
} // MEGEngine