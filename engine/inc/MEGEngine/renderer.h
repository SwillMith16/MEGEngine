#ifndef MEGENGINEPROJECT_RENDERER_H
#define MEGENGINEPROJECT_RENDERER_H

#include <memory>
#include <vector>

#include "MEGEngine/common.h"

namespace MEGEngine {
    class ENGINE_API Renderer {
    public:
        Renderer() = default;
        ~Renderer() = default;

        void init();
        void render(const class Scene& scene);

    private:
        void draw(class Entity& entity, const class Scene& scene);
        void drawMeshes(std::vector<std::unique_ptr<class Entity>&> entities);

        bool _initialised = false;
        struct RenderGroup;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_RENDERER_H