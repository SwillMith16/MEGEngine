#ifndef MESH_H
#define MESH_H

#include <vector>

#include "MEGEngine/common.h"
#include "MEGEngine/vao.h"
#include "MEGEngine/vertex.h"
#include "MEGEngine/texture.h"

namespace MEGEngine {
	class ENGINE_API Mesh {
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		void bind();
		size_t numIndices();

	private:
		VAO vao;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
	};
}


#endif //MESH_H