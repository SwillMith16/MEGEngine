#ifndef MODEL_H
#define MODEL_H

#include <JSON/json.hpp>

#include "common.h"

#include "GLM/gtx/quaternion.hpp"

#include "math/mat4.h"
#include "math/vec3.h"
#include "math/vec2.h"

using json = nlohmann::json;

namespace MEGEngine {
	class ENGINE_API Model {
	public:
		Vec3 transform = Vec3(0.0f, 0.0f, 0.0f);
		glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		float scale = 1.0f;

		Model(const char* file);
		void draw(class Shader& shader, class Camera& camera);

	private:
		const char* file;
		std::vector<unsigned char> data;
		json JSON;

		std::vector<class Mesh> meshes;
		std::vector<Vec3> translationsMeshes;
		std::vector<glm::quat> rotationsMeshes;
		std::vector<Vec3> scalesMeshes;
		std::vector<Mat4> matricesMeshes;

		std::vector<std::string> loadedTexName;
		std::vector<class Texture> loadedTex;

		void loadMesh(unsigned int indMesh);

		void traverseNode(unsigned int nextNode, Mat4 matrix = Mat4(1.0f));

		std::vector<unsigned char> getData();
		std::vector<float> getFloats(json accessor);
		std::vector<unsigned int> getIndices(json accessor);
		std::vector<Texture> getTextures();

		std::vector<struct Vertex> assembleVertices(std::vector<Vec3> positions, std::vector<Vec3> normals, std::vector<Vec2> texUVs);

		std::vector<Vec2> groupFloatsVec2(std::vector<float> floatVec);
		std::vector<Vec3> groupFloatsVec3(std::vector<float> floatVec);
		std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
	};
}


#endif //MODEL_H