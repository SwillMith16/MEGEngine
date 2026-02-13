#version 330 core

// vertex coordinates
layout (location = 0) in vec3 aPos;

// normal vector
layout (location = 1) in vec3 aNormal;

// colours
layout (location = 2) in vec3 aColour;

// texture coordinates
layout (location = 3) in vec2 aTex;


// outputs colour and texture coordinates to fragment shader
out vec3 currentPos;
out vec3 normal;
out vec3 colour;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
    currentPos = vec3(model * vec4(aPos, 1.0f));
    normal = vec3(rotation * vec4(aNormal, 1.0f));
    colour = aColour;
    texCoord = aTex;

    gl_Position = camMatrix * vec4(currentPos, 1.0f);
}