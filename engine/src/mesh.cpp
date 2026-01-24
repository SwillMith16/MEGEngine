#include "mesh.h"
#include "ebo.h"

namespace MEGEngine {
	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
		this->vertices = vertices;
		this->indices = indices;

		vao.bind();
		VBO vbo(vertices);
		EBO ebo(indices);

		vao.linkAttrib(vbo, 0, 3, sizeof(Vertex), (void *) 0); // position
		vao.linkAttrib(vbo, 1, 3, sizeof(Vertex), (void *) (3 * sizeof(float))); // normal
		vao.linkAttrib(vbo, 2, 3, sizeof(Vertex), (void *) (6 * sizeof(float))); // colour
		vao.linkAttrib(vbo, 3, 2, sizeof(Vertex), (void *) (9 * sizeof(float))); // texture UV
		vao.unbind();
		vbo.unbind();
		ebo.unbind();
	}

	void Mesh::bind() {
		vao.bind();
	}

	size_t Mesh::numIndices() {
		return this->indices.size();
	}
}
