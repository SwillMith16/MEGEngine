#version 330 core

out vec4 fragColour;

uniform vec4 materialColour;

void main()
{
    fragColour = vec4(materialColour.x, materialColour.y, materialColour.z, 0.0f);
}