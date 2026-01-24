#ifndef MESH_H
#define MESH_H

#include "common.h"

#include "vao.h"
#include "vertex.h"
#include "texture.h"

namespace MEGEngine {
	class ENGINE_API Mesh {
	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
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