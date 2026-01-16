//
// Created by Will on 07/12/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "shader.h"

class Camera {
public:
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 camMatrix = glm::mat4(1.0f);

	glm::vec3 position;

    // Used to prevent camera from jumping on click
    bool firstClick = true;

    // Used to check if input state has just changed from PRESS to RELEASE, and return mouse to it's initial position
    int lastMouseInputState;
    double initialMouseX, initialMouseY;

    float speed = 20.0f;
	float baseSpeed = 20.0f;
	float boostSpeed = 50.0f;
    float sensitivity = 100.0f;

    Camera(int width, int height, glm::vec3 position);

	glm::vec3 getPosition();
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void matrix(Shader& shader, const char* uniform);
    void processInputs(GLFWwindow* window);

private:
	int _width;
	int _height;

};


#endif //CAMERA_H