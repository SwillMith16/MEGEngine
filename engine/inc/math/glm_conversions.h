#ifndef MEGENGINE_GLM_CONVERSIONS_H
#define MEGENGINE_GLM_CONVERSIONS_H

#include "GLM/vec3.hpp"
#include "GLM/vec2.hpp"

#include "math/vec3.h"
#include "math/vec2.h"

namespace MEGEngine::Private {
	inline glm::vec3 toGlmVec3(const Vec3& v) {
		return {v.x, v.y, v.z};
	}

	inline Vec3 fromGlmVec3(const glm::vec3& v) {
		return {v.x, v.y, v.z};
	}

	inline glm::vec2 toGlmVec2(const Vec2& v) {
		return {v.x, v.y};
	}

	inline Vec2 fromGlmVec2(const glm::vec2& v) {
		return {v.x, v.y};
	}
}

#endif //MEGENGINE_GLM_CONVERSIONS_H