#include "math/vec2.h"
#include "math/glm_conversions.h"

#include "GLM/glm.hpp"

namespace MEGEngine {

	Vec2 Vec2::operator+(const Vec2 &v) const {
		// convert this and other vec to glm, perform addition and convert back to return Vec3
		return Private::fromGlmVec2(Private::toGlmVec2(*this) + Private::toGlmVec2(v));
	}

	Vec2 Vec2::operator-(const Vec2 &v) const {
		return Private::fromGlmVec2(Private::toGlmVec2(*this) - Private::toGlmVec2(v));
	}

	Vec2 Vec2::operator-() const {
		return (*this * -1);
	}

	Vec2 Vec2::operator*(float scalar) const {
		return Private::fromGlmVec2(Private::toGlmVec2(*this) * scalar);
	}

	Vec2 operator*(float scalar, const Vec2 &v) {
		return v * scalar;
	}

	Vec2 Vec2::operator+=(const Vec2 &v) {
		*this = *this + v;
		return *this;
	}

	Vec2 Vec2::operator-=(const Vec2 &v) {
		*this = *this - v;
		return *this;
	}

	Vec2 Vec2::operator*=(float scalar) {
		*this = *this * scalar;
		return *this;
	}


	float Vec2::length() const {
		return glm::length(Private::toGlmVec2(*this));
	}

	Vec2 Vec2::normalized() const {
		return Private::fromGlmVec2(glm::normalize(Private::toGlmVec2(*this)));
	}

	float Vec2::dot(const Vec2 &a, const Vec2& b) {
		return glm::dot(Private::toGlmVec2(a), Private::toGlmVec2(b));
	}
} // MEGEngine