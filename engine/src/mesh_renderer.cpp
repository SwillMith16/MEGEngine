#include "GLAD/glad.h"

#include "mesh_renderer.h"

#include <utility>
#include "camera.h"
#include "material.h"
#include "shader.h"
#include "mesh.h"
#include "transform.h"

#include "math/vec3.h"
#include "math/quat.h"
#include "utils/log.h"

namespace MEGEngine {
    MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<class Material> material)
        : _mesh(std::move(mesh)), _material(std::move(material)) {}

    void MeshRenderer::setMaterial(std::shared_ptr<class Material> material) {
        _material = std::move(material);
    }

    std::shared_ptr<Material> MeshRenderer::material() {
        return _material;
    }

    std::shared_ptr<class Mesh> MeshRenderer::mesh() {
        return _mesh;
    }

    void MeshRenderer::draw(Camera& camera, Transform& transform) {
        if (!_material->shader()) {
            Log(LogLevel::WRN, "Attempt to draw failed. Shader is null");
            return;
        }

        _material->bind();
        _mesh->bind();

        // Keep track of how many of each type of textures we have
        unsigned int numDiffuse = 0;
        unsigned int numSpecular = 0;

        for (unsigned int i = 0; i < _material->textures().size(); i++)
        {
            std::string num;
            std::string type = _material->textures()[i].type;
            if (type == "diffuse")
            {
                num = std::to_string(numDiffuse++);
            }
            else if (type == "specular")
            {
                num = std::to_string(numSpecular++);
            }
            _material->textures()[i].texUnit(*_material->shader().get(), (type + num).c_str(), i);
            _material->textures()[i].bind();
        }
        _material->shader()->setUniform("camPos", camera.transform().position());
        camera.matrix(*_material->shader().get(), "camMatrix");

        // Create matrices
        Mat4 trans = Mat4::translation(transform.position());
        Mat4 rot = transform.rotation().toMatrix();
        Mat4 sca = Mat4::scale(transform.scale());

        // Push the matrices to the vertex shader
        Mat4 modelMatrix = transform.modelMatrix();
        _material->shader()->setUniform("model",  modelMatrix);
        _material->shader()->setUniform("translation", trans);
        _material->shader()->setUniform("rotation", rot);
        _material->shader()->setUniform("scale", sca);

        // Draw the actual mesh
        glDrawElements(GL_TRIANGLES, _mesh->numIndices(), GL_UNSIGNED_INT, 0);
    }
} // MEGEngine