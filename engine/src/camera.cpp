#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "GLM/gtc/type_ptr.hpp"
#include "GLM/gtx/rotate_vector.hpp"
#include "GLM/gtx/vector_angle.hpp"

#include "camera.h"
#include "window.h"

#include "math/glm_conversions.h"

#include "utils/log.h"

namespace MEGEngine {

    struct WindowImpl {
        GLFWwindow* impl;
    };

    Camera::Camera(int width, int height) :
        _width(static_cast<float>(width)),
        _height(static_cast<float>(height)),
        initialMouseX(float(width)),
        initialMouseY(float(height)),
        lastMouseInputState(GLFW_RELEASE){}

    Transform& Camera::transform() {
        return *_transform;
    }


    void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
        Mat4 view = Mat4(1.0f);
        Mat4 projection = Mat4(1.0f);

        view = Private::fromGlmMat4(glm::lookAt(Private::toGlmVec3(_transform->position()), Private::toGlmVec3(_transform->position() + orientation), Private::toGlmVec3(up)));
        projection = Private::fromGlmMat4(glm::perspective(glm::radians(FOVdeg), (float)_width / _height, nearPlane, farPlane));

        // set new camera matrix
        camMatrix = projection * view;
    }

    void Camera::matrix(Shader& shader, const char* uniform) {
        // export camera matrix to shader
        shader.setUniform(uniform,  camMatrix);
    }


    void Camera::processInputs(Window& window, float deltaTime) {
        WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&window.impl()));
        // Handles key inputs
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_W) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "W key pressed");
            _transform->setPosition(_transform->position() + (speed * deltaTime * orientation));
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_A) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "A key pressed");
            _transform->setPosition(_transform->position() - (speed * deltaTime * Vec3::cross(orientation, up).normalized()));
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_S) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "S key pressed");
            _transform->setPosition(_transform->position() - (speed * deltaTime * orientation));
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_D) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "D key pressed");
            _transform->setPosition(_transform->position() + (speed * deltaTime * Vec3::cross(orientation, up).normalized()));
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "Space key pressed");
            _transform->setPosition(_transform->position() + (speed * deltaTime * up));
        }
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            Log(LogLevel::DBG, "L-Ctrl key pressed");
            _transform->setPosition(_transform->position() - (speed * deltaTime * up));
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
            Vec3 newOrientation = Private::fromGlmVec3(glm::rotate(Private::toGlmVec3(orientation), glm::radians(-rotX), glm::normalize(glm::cross(Private::toGlmVec3(orientation), Private::toGlmVec3(up)))));

            // Decides whether or not the next vertical Orientation is legal or not
            if (abs(glm::angle(Private::toGlmVec3(newOrientation), Private::toGlmVec3(up)) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                orientation = newOrientation;
            }

            // Rotates the Orientation left and right
            orientation = Private::fromGlmVec3(glm::rotate(Private::toGlmVec3(orientation), glm::radians(-rotY), Private::toGlmVec3(up)));

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