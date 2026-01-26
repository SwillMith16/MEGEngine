#ifndef MEGENGINEPROJECT_SCENE_H
#define MEGENGINEPROJECT_SCENE_H

#include <memory>
#include <vector>

#include "common.h"
#include "entity.h"

namespace MEGEngine {
    class ENGINE_API Scene {
    public:
        Scene();
        ~Scene() = default;

        void update(float dt);

        const std::vector<std::unique_ptr<Entity>>& entities() const;

        Entity& createEntity();

        Camera& camera() const;

    private:
        std::vector<std::unique_ptr<Entity>> _entities;
        std::unique_ptr<Camera> _camera;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_SCENE_H