#ifndef MEGENGINE_GLM_CONVERSIONS_H
#define MEGENGINE_GLM_CONVERSIONS_H

#include <cstring>

#include "GLM/vec2.hpp"
#include "GLM/vec3.hpp"
#include "GLM/vec4.hpp"
#include "GLM/mat4x4.hpp"
#include "GLM/gtc/quaternion.hpp"
#include "GLM/gtx/quaternion.hpp"

#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"
#include "math/quat.h"

namespace MEGEngine::Private {

	inline glm::vec2 toGlmVec2(const Vec2& v) {
		return {v.x, v.y};
	}

	inline Vec2 fromGlmVec2(const glm::vec2& v) {
		return {v.x, v.y};
	}



	inline glm::vec3 toGlmVec3(const Vec3& v) {
		return {v.x, v.y, v.z};
	}

	inline Vec3 fromGlmVec3(const glm::vec3& v) {
		return {v.x, v.y, v.z};
	}



	inline glm::vec4 toGlmVec4(const Vec4& v) {
		return {v.x, v.y, v.z, v.w};
	}

	inline Vec4 fromGlmVec4(const glm::vec4& v) {
		return {v.x, v.y, v.z, v.w};
	}



	inline glm::mat4 toGlmMat4(const Mat4& m)
	{
		glm::mat4 out;
		std::memcpy(&out[0][0], m.m, sizeof(float) * 16);
		return out;
	}

	inline Mat4 fromGlmMat4(const glm::mat4& m)
	{
		Mat4 out;
		std::memcpy(out.m, &m[0][0], sizeof(float) * 16);
		return out;
	}


	inline glm::quat toGlmQuat(const Quat& q) {
		glm::quat out(q.w, q.x, q.y, q.z);
		return out;
	}

	inline Quat fromGlmQuat(const glm::quat& q) {
		Quat out(q.x, q.y, q.z, q.w);
		return out;
	}
}

#endif //MEGENGINE_GLM_CONVERSIONS_H