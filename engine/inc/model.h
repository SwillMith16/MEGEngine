//
// Created by Will on 28/12/2025.
//

#ifndef MODEL_H
#define MODEL_H

#include <JSON/json.hpp>
#include "mesh.h"

using json = nlohmann::json;


class Model {
public:
	glm::vec3 transform = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	GLfloat scale = 1.0f;

	Model(const char* file);
	void draw(Shader& shader, Camera& camera);

private:
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	void loadMesh(unsigned int indMesh);

	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	std::vector<unsigned char> getData();
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accesor);
	std::vector<Texture> getTextures();

	std::vector<Vertex> assembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> texUVs);

	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};


#endif //MODEL_H