#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include "common.h"
#include "shader.h"
#include "transform.h"
#include "math/vec3.h"
#include "math/mat4.h"

namespace MEGEngine {
	class ENGINE_API Camera {
	public:
		Vec3 _orientation = Vec3(0.0f, 0.0f, -1.0f);
		Vec3 _up = Vec3(0.0f, 1.0f, 0.0f);
		Mat4 camMatrix = Mat4(1.0f);

		// Used to prevent camera from jumping on click
		bool firstClick = true;

		// Used to check if input state has just changed from PRESS to RELEASE, and return mouse to it's initial position
		int lastMouseInputState;
		double initialMouseX, initialMouseY;

		float speed = 5.0f;
		float baseSpeed = 5.0f;
		bool isSprinting = false;
		float boostSpeed = 10.0f;
		float sensitivity = 100.0f;

		Camera(int width, int height);

		Transform& transform() const;

		void updateMatrix();
		void matrix(Shader& shader, const char* uniform) const;
		void processInputs(class Window& window, float deltaTime);

		Mat4 viewMatrix() const;
		Mat4 projectionMatrix() const;

	private:
		float _width;
		float _height;

		float _fov;
		float _nearZ;
		float _farZ;

		std::unique_ptr<Transform> _transform = std::make_unique<Transform>();
	};
}


#endif //CAMERA_H