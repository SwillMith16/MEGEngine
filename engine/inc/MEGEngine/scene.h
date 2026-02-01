#ifndef MEGENGINEPROJECT_SCENE_H
#define MEGENGINEPROJECT_SCENE_H

#include <memory>
#include <vector>

#include "MEGEngine/common.h"
#include "MEGEngine/entity.h"
#include "MEGEngine/light.h"
#include "MEGEngine/camera.h"

namespace MEGEngine {
    class ENGINE_API Scene {
    public:
        Scene(float width, float height);
        ~Scene() = default;

        // Template allows for creation of entities AND entity sub-types.
        // i.e. lights, which can have a colour without requiring a mesh renderer
        template<typename T>
        T& createEntity()
        {
            static_assert(std::is_base_of_v<Entity, T>);

            auto entity = std::make_unique<T>();
            T& ref = *entity;
            _entities.push_back(std::move(entity));

            return ref;
        }

        // Special entity creation for camera type.
        template<typename T>
        T& createEntity(float width, float height);

        void update();

        const std::vector<std::unique_ptr<Entity>>& entities() const;

        const std::vector<LightData>& lightData() const;

        Camera& camera() const;

    private:
        std::vector<std::unique_ptr<Entity>> _entities;
        std::vector<LightData> _lightData;
        Camera* _camera = nullptr;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_SCENE_H