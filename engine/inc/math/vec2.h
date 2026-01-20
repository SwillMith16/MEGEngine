#ifndef MEGENGINE_VEC2_H
#define MEGENGINE_VEC2_H

namespace MEGEngine {
	struct Vec2 {
		// Member vars
		float x, y;

		// Constructors
		constexpr Vec2() : x(0), y(0) {}
		constexpr Vec2(float x, float y) : x(x), y(y) {}

		// Operators
		Vec2 operator+ (const Vec2 &v) const;
		Vec2 operator- (const Vec2 &v) const;
		Vec2 operator* (float scalar) const;

		Vec2 operator+= (const Vec2 &v);
		Vec2 operator-= (const Vec2 &v);
		Vec2 operator*= (float scalar);

		// utility functions
		float length() const;
		Vec2 normalized() const;
		static float dot(const Vec2 &a, const Vec2 &b);
	};
} // MEGEngine

#endif //MEGENGINE_VEC2_H