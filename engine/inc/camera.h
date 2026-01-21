#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "shader.h"
#include "math/vec3.h"
#include "math/mat4.h"

namespace MEGEngine {
	class ENGINE_API Camera {
	public:
		Vec3 orientation = Vec3(0.0f, 0.0f, -1.0f);
		Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
		Mat4 camMatrix = Mat4(1.0f);

		Vec3 position;

		// Used to prevent camera from jumping on click
		bool firstClick = true;

		// Used to check if input state has just changed from PRESS to RELEASE, and return mouse to it's initial position
		int lastMouseInputState;
		double initialMouseX, initialMouseY;

		float speed = 5.0f;
		float baseSpeed = 5.0f;
		float boostSpeed = 10.0f;
		float sensitivity = 100.0f;

		Camera(int width, int height, Vec3 position);

		Vec3 getPosition();
		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void matrix(Shader& shader, const char* uniform);
		//void processInputs(GLFWwindow* window, float deltaTime);

	private:
		float _width;
		float _height;
	};
}


#endif //CAMERA_H