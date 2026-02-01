#ifndef CAMERA_H
#define CAMERA_H

#include "MEGEngine/common.h"
#include "MEGEngine/entity.h"
#include "MEGEngine/math/mat4.h"

namespace MEGEngine {
	class ENGINE_API Camera : public Entity {
	public:
		Camera(int width, int height);
		void onUpdate() override;

		Mat4 camMatrix() const;
		void processInputs(class Window& window);

	private:
		float _width;
		float _height;

		float _fov;
		float _nearZ;
		float _farZ;

		Mat4 _camMatrix = Mat4(1.0f);

		// Used to check if input state has just changed from PRESS to RELEASE, and return mouse to it's initial position
		int lastMouseInputState;
		double initialMouseX, initialMouseY;

		// Used to prevent camera from jumping on click
		bool firstClick = true;

		float speed = 5.0f;
		float baseSpeed = 5.0f;
		bool isSprinting = false;
		float boostSpeed = 10.0f;
		float sensitivity = 100.0f;
	};
}


#endif //CAMERA_H