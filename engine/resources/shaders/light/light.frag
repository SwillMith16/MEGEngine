#version 330 core

out vec4 fragColour;

uniform vec4 lightColour;

void main()
{
    fragColour = vec4(lightColour.x, lightColour.y, lightColour.z, 0.0f);
}