#version 330 core

in vec3 currentPos;
in vec3 normal;
in vec3 colour;
in vec2 texCoord;

out vec4 fragColour;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform int useTex;
uniform vec4 materialColour;

uniform vec4 lightColour;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight() {
    vec3 lightVec = lightPos - currentPos;
    float dist = length(lightVec);
    float a = 0.00005;
    float b = 0.00001;
    float intensity = 1.0f / (a*(dist * dist) + b*dist + 1.0f);

    // ambient (world) lighting
    float ambient = 0.2f;

    // diffuse lighting (from a light source)
    vec3 _normal = normalize(normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(_normal, lightDirection), 0.0f);

    vec4 finalLighting = vec4(0);

    // final basic lighting
    if (useTex == 0) {
        finalLighting = vec4(materialColour * ((diffuse * intensity) + ambient));
    } else {
        finalLighting = vec4(texture(diffuse0, texCoord) * ((diffuse * intensity) + ambient));
    }

    // specular lighting
    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, _normal); // negative as you want the reflection towards the plane
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 15);
    float specular = specAmount * specularLight;

    vec4 finalSpecular;
    if (useTex == 0) {
        finalSpecular = vec4(0);
    } else {
        finalSpecular = vec4(texture(specular0, texCoord).r * specular * intensity);
    }

    return (finalLighting + finalSpecular) * lightColour;
}

vec4 directLight() {
    // ambient (world) lighting
    float ambient = 0.2f;

    // diffuse lighting (from a light source)
    vec3 _normal = normalize(normal);
    vec3 lightDirection = normalize(vec3(-1.0f, 0.0f, 0.0f));
    float diffuse = max(dot(_normal, lightDirection), 0.0f);

    // final basic lighting
    if (useTex == 0) {
        finalLighting = vec4(materialColour * ((diffuse * intensity) + ambient));
    } else {
        finalLighting = vec4(texture(diffuse0, texCoord) * ((diffuse * intensity) + ambient));
    }

    // specular lighting
    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, _normal); // negative as you want the reflection towards the plane
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 15);
    float specular = specAmount * specularLight;

    vec4 finalSpecular;
    if (useTex == 0) {
        finalSpecular = vec4(0);
    } else {
        finalSpecular = vec4(texture(specular0, texCoord).r * specular * intensity);
    }

    return (finalLighting + finalSpecular) * lightColour;
}

vec4 spotLight() {
    float outerCone = 0.9f; // value input to cosine i.e. cos(value) instead of using degrees - saves computation
    float innerCone = 0.95f;

    // ambient (world) lighting
    float ambient = 0.2f;

    // diffuse lighting (from a light source)
    vec3 _normal = normalize(normal);
    vec3 lightDirection = normalize(lightPos - currentPos);
    float diffuse = max(dot(_normal, lightDirection), 0.0f);

    // specular lighting
    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, _normal); // negative as you want the reflection towards the plane
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 15);
    float specular = specAmount * specularLight;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    if (useTex == 0) {
        finalLighting = vec4(materialColour * ((diffuse * intensity) + ambient));
    } else {
        finalLighting = vec4(texture(diffuse0, texCoord) * ((diffuse * intensity) + ambient));
    }

    vec4 finalSpecular;
    if (useTex == 0) {
        finalSpecular = vec4(0);
    } else {
        finalSpecular = vec4(texture(specular0, texCoord).r * specular * intensity);
    }

    return (finalLighting + finalSpecular) * lightColour;
}

void main() {
    fragColour = pointLight();
//    fragColour = directLight();
//    fragColour = spotLight();
}