#include "MEGEngine/mesh_renderer.h"
#include "MEGEngine/material.h"
#include "MEGEngine/mesh.h"

namespace MEGEngine {
    MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
        : _mesh(std::move(mesh)), _material(std::move(material)) {}

    void MeshRenderer::setMaterial(std::shared_ptr<Material> material) {
        _material = std::move(material);
    }

    std::shared_ptr<Material> MeshRenderer::material() const {
        return _material;
    }

    std::shared_ptr<Mesh> MeshRenderer::mesh() const {
        return _mesh;
    }
} // MEGEngine