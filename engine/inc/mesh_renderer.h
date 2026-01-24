#ifndef MEGENGINEPROJECT_MESH_RENDERER_H
#define MEGENGINEPROJECT_MESH_RENDERER_H

#include <memory>

#include "common.h"

namespace MEGEngine {
    class ENGINE_API MeshRenderer {
    public:
        MeshRenderer(std::shared_ptr<class Mesh> mesh, std::shared_ptr<class Material> material);
        std::shared_ptr<class Material> material();
        std::shared_ptr<class Mesh> mesh();

        void draw(class Camera& camera, class Mat4 matrix, class Vec3 transform, class Quat rotation, class Vec3 scale);

    private:
        std::shared_ptr<class Mesh> _mesh;
        std::shared_ptr<class Material> _material;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_MESH_RENDERER_H