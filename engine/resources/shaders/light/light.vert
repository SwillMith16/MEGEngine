#version 330 core

// vertex coordinates
layout (location = 0) in vec3 aPos;

out vec3 currentPos;

uniform mat4 model;
uniform mat4 translation;
uniform mat4 camMatrix;

void main()
{
    currentPos = vec3(model * vec4(aPos, 1.0f));
    gl_Position = camMatrix * vec4(currentPos, 1.0f);
}