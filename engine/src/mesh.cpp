//
// Created by Will on 26/12/2025.
//

#include "mesh.h"

#include <iostream>

namespace MEGEngine {
	Mesh::Mesh(std::vector<MEGEngine::Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		vao.bind();
		MEGEngine::VBO vbo(vertices);
		EBO ebo(indices);

		vao.linkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(MEGEngine::Vertex), (void *) 0); // position
		vao.linkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(MEGEngine::Vertex), (void *) (3 * sizeof(float))); // normal
		vao.linkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(MEGEngine::Vertex), (void *) (6 * sizeof(float))); // colour
		vao.linkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(MEGEngine::Vertex), (void *) (9 * sizeof(float))); // texture UV
		vao.unbind();
		vbo.unbind();
		ebo.unbind();
	}

	void Mesh::draw
	( // parameters
		Shader& shader,
		Camera& camera,
		glm::mat4 matrix,
		glm::vec3 transform,
		glm::quat rotation,
		glm::vec3 scale
	)
	{ // body
		// Bind shader to be able to access uniforms
		shader.activate();
		vao.bind();

		// Keep track of how many of each type of textures we have
		unsigned int numDiffuse = 0;
		unsigned int numSpecular = 0;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			std::string num;
			std::string type = textures[i].type;
			if (type == "diffuse")
			{
				num = std::to_string(numDiffuse++);
			}
			else if (type == "specular")
			{
				num = std::to_string(numSpecular++);
			}
			textures[i].texUnit(shader, (type + num).c_str(), i);
			textures[i].bind();
		}
		// Take care of the camera Matrix
		shader.setUniform("camPos", camera.position);
		camera.matrix(shader, "camMatrix");

		// Initialize matrices
		glm::mat4 trans = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 sca = glm::mat4(1.0f);

		// Transform the matrices to their correct form
		transform.z = -transform.z;
		trans = glm::translate(trans, transform);
		rot = glm::mat4_cast(rotation);
		sca = glm::scale(sca, scale);

		// Push the matrices to the vertex shader
		shader.setUniform("model", matrix);
		shader.setUniform("translation", trans);
		shader.setUniform("rotation", rot);
		shader.setUniform("scale", sca);

		// Draw the actual mesh
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
}