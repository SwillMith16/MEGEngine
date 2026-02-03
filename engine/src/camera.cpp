#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "GLM/gtc/type_ptr.hpp"
#include "GLM/gtx/rotate_vector.hpp"
#include "GLM/gtx/vector_angle.hpp"

#include "MEGEngine/camera.h"
#include "MEGEngine/window.h"
#include "MEGEngine/timer.h"

#include "MEGEngine/math/glm_conversions.h"

#include "MEGEngine/utils/log.h"

namespace MEGEngine {

    struct WindowImpl {
        GLFWwindow* impl;
    };

    Camera::Camera(int width, int height) :
        _width(static_cast<float>(width)),
        _height(static_cast<float>(height)),
        _fov(75.0f),
        _nearZ(0.1f),
        _farZ(1000.0f),
        initialMouseX(float(width)),
        initialMouseY(float(height)),
        lastMouseInputState(GLFW_RELEASE) {}

    void Camera::onUpdate() {
        Vec3 camForward = transform().orientation().rotate(Vec3::worldForward());
        Mat4 view = Mat4::lookAt(
            _transform->position(),
            _transform->position() + camForward,
            Vec3::worldUp()
            );

        Mat4 projection = Mat4::perspective(_fov, _width/_height, _nearZ, _farZ);

        _camMatrix = projection * view;
    }

    Mat4 Camera::camMatrix() const {
        return _camMatrix;
    }


    void Camera::processInputs(Window& window) {
        WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&window.impl()));
        // Handles key inputs
        Vec3 localMove(0, 0, 0);
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_W) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "W key pressed");
            localMove.z += 1;
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_A) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "A key pressed");
            localMove.x -= 1;
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_S) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "S key pressed");
            localMove.z -= 1;
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_D) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "D key pressed");
            localMove.x += 1;
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "Space key pressed");
            localMove.y += 1;
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "L-Ctrl key pressed");
            localMove.y -= 1;
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "L-Shift key pressed");
            isSprinting = true;
            speed = boostSpeed;
        }
        else if (glfwGetKey(glfwWindow->impl, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE && isSprinting)
        {
            isSprinting = false;
            Log(LogLevel::DBG, "L-Shift key released");
            speed = baseSpeed;
        }

        if (localMove.length() * localMove.length() > 0) {
            localMove = localMove.normalized();

            Vec3 worldMove = transform().orientation().rotate(localMove);
            transform().setPosition(transform().position() + (worldMove * speed * Timer::deltaTime()));
        }


        if (glfwGetMouseButton(glfwWindow->impl, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            glfwSetInputMode(glfwWindow->impl, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            // Prevents camera from jumping on the first click
            if (firstClick)
            {
                glfwGetCursorPos(glfwWindow->impl, &initialMouseX, &initialMouseY);
                glfwSetCursorPos(glfwWindow->impl, (_width / 2), (_height / 2));
                firstClick = false;
            }

            double mouseX, mouseY;
            glfwGetCursorPos(glfwWindow->impl, &mouseX, &mouseY);

            float rotX = sensitivity * ((float)mouseY - (_height/2)) / _height;
            float rotY = sensitivity * ((float)mouseX - (_width/2)) / _width;

            // Calculates upcoming vertical change in the Orientation
            Quat tmpOrientation = _transform->orientation();

            Vec3 camRight = _transform->orientation().rotate(Vec3::worldRight());
            Quat pitch = Quat::fromAxisAngle(camRight, glm::radians(rotX));
            tmpOrientation = pitch * tmpOrientation;

            Vec3 camForward = tmpOrientation.rotate(Vec3::worldForward());
            float pitchAngle = glm::degrees(std::asin(glm::clamp(camForward.y, -1.0f, 1.0f)));

            // Decides whether or not the next vertical Orientation is legal or not
            if (pitchAngle > -85.0f && pitchAngle < 85.0f)
            {
                _transform->setOrientation(tmpOrientation);
            }

            // Rotates the Orientation left and right
            Quat yaw = Quat::fromAxisAngle(Vec3::worldUp(), glm::radians(rotY));
            _transform->setOrientation(yaw * _transform->orientation().normalised());

            // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
            glfwSetCursorPos(glfwWindow->impl, (_width / 2), (_height / 2));

            lastMouseInputState = GLFW_PRESS;
        }
        else if (glfwGetMouseButton(glfwWindow->impl, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {

            // only need to process this if the state has just changed, not constantly when button not pressed
            if (lastMouseInputState == GLFW_PRESS) {
                // Makes sure the next time the camera looks around it doesn't jump
                firstClick = true;

                // return cursor to position it was in
                glfwSetCursorPos(glfwWindow->impl, initialMouseX, initialMouseY);

                glfwSetInputMode(glfwWindow->impl, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

                lastMouseInputState = GLFW_RELEASE;
            }

        }
    }

}