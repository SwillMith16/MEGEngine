//
// Created by Will on 07/12/2025.
//

#include "camera.h"
#include "timer.h"

Camera::Camera(int width, int height, glm::vec3 position) {
    _width = width;
    _height = height;
    this->position = glm::vec3(position.x, position.y, -position.z);
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(position, position + orientation, up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)_width / _height, nearPlane, farPlane);

    // set new camera matrix
    camMatrix = projection * view;
}

void Camera::matrix(Shader& shader, const char* uniform) {
	// export camera matrix to shader
	shader.setUniform(uniform, camMatrix);
}

void Camera::processInputs(GLFWwindow* window) {
    // Handles key inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += speed * Time.deltaTime() * orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position += speed * Time.deltaTime() * -glm::normalize(glm::cross(orientation, up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position += speed * Time.deltaTime() * -orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += speed * Time.deltaTime() * glm::normalize(glm::cross(orientation, up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position += speed * Time.deltaTime() * up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        position += speed * Time.deltaTime() * -up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        speed = boostSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        speed = baseSpeed;
    }



    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Prevents camera from jumping on the first click
        if (firstClick)
        {
            glfwGetCursorPos(window, &initialMouseX, &initialMouseY);
            glfwSetCursorPos(window, (_width / 2), (_height / 2));
            firstClick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - ((float)_height/2)) / _height;
        float rotY = sensitivity * (float)(mouseX - ((float)_width/2)) / _width;

        // Calculates upcoming vertical change in the Orientation
        glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

        // Decides whether or not the next vertical Orientation is legal or not
        if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            orientation = newOrientation;
        }

        // Rotates the Orientation left and right
        orientation = glm::rotate(orientation, glm::radians(-rotY), up);

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        glfwSetCursorPos(window, (_width / 2), (_height / 2));

        lastMouseInputState = GLFW_PRESS;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {

        // only need to process this if the state has just changed, not constantly when button not pressed
        if (lastMouseInputState == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            // Makes sure the next time the camera looks around it doesn't jump
            firstClick = true;

            // return cursor to position it was in
            glfwSetCursorPos(window, initialMouseX, initialMouseY);

            lastMouseInputState = GLFW_RELEASE;
        }

    }
}