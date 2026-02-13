#ifndef MEGENGINE_VEC3_H
#define MEGENGINE_VEC3_H

#include "MEGEngine/common.h"

namespace MEGEngine {
	class ENGINE_API Vec3 {
	public:
		// Member vars
		float x, y, z;

		// Constructors
		constexpr Vec3() : x(0), y(0), z(0) {}
		constexpr Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

		// Operators
		Vec3 operator+ (const Vec3 &v) const;
		Vec3 operator- (const Vec3 &v) const;
		Vec3 operator- () const;
		Vec3 operator* (float scalar) const;

		Vec3 operator+= (const Vec3 &v);
		Vec3 operator-= (const Vec3 &v);
		Vec3 operator*= (float scalar);

		// utility functions
		float length() const;
		Vec3 normalized() const;
		static float dot(const Vec3 &a, const Vec3 &b);
		static Vec3 cross(const Vec3 &a, const Vec3 &b);

		static Vec3 worldRight() { return {1, 0, 0}; }
		static Vec3 worldUp() { return {0, 1, 0}; }
		static Vec3 worldForward() { return {0, 0, 1}; }
	};

	Vec3 operator* (float scalar, const Vec3 &v);
} // MEGEngine

#endif //MEGENGINE_VEC3_H