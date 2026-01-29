#ifndef MEGENGINEPROJECT_RENDERER_H
#define MEGENGINEPROJECT_RENDERER_H

#include <memory>
#include <vector>

#include "common.h"

namespace MEGEngine {
    class ENGINE_API Renderer {
    public:
        Renderer() = default;
        ~Renderer() = default;

        void init();
        void render(const class Scene& scene);

    private:
        void drawMesh(const class MeshRenderer& mr, const class Transform& transform, const class Camera& camera);
        void drawMeshes(std::vector<std::unique_ptr<class Entity>&> entities);

        bool _initialised = false;
        struct RenderGroup;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_RENDERER_H