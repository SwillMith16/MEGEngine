#ifndef MESH_H
#define MESH_H

#include "common.h"

#include "vao.h"
#include "vertex.h"
#include "texture.h"

#include "math/quat.h"
#include "math/mat4.h"
#include "math/vec3.h"

namespace MEGEngine {
	class ENGINE_API Mesh {
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		// float scale = 1.0f;

		VAO vao;

		Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);

		void draw
		(
			class Shader& shader,
			class Camera& camera,
			Mat4 matrix = Mat4(1.0f),
			Vec3 transform = Vec3(0.0f, 0.0f, 0.0f),
			Quat rotation = Quat(1.0f, 0.0f, 0.0f, 0.0f),
			Vec3 scale = Vec3(1.0f, 1.0f, 1.0f)
		);
	};
}


#endif //MESH_H