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

    std::shared_ptr<Material> MeshRenderer::material() const {
        return _material;
    }

    std::shared_ptr<class Mesh> MeshRenderer::mesh() const {
        return _mesh;
    }
} // MEGEngine