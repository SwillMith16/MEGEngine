#include "MEGEngine/scene.h"
#include "MEGEngine/camera.h"

namespace MEGEngine {
    Scene::Scene(float width, float height) {
        createEntity<Camera>(width, height);
    }

    template<typename T>
    T& Scene::createEntity(float width, float height) {
        static_assert(std::is_base_of_v<Entity, T>);

        auto entity = std::make_unique<T>(width, height);
        T& ref = *entity;
        _entities.push_back(std::move(entity));

        if (std::is_base_of_v<Camera, T>)
            _camera = &ref;

        return ref;
    }
    template Camera& Scene::createEntity<Camera>(float width, float height);

    const std::vector<std::unique_ptr<Entity>>& Scene::entities() const {
        return _entities;
    }

    const std::vector<LightData>& Scene::lightData() const {
        return _lightData;
    }

    Camera& Scene::camera() const {
        return *_camera;
    }

    void Scene::update() {
        // trigger updates for each entity in the scene
        for (auto& entity : _entities) {
            entity->onUpdate();
        }

        // clear and refresh scene light data
        _lightData.clear();
        for (auto& entity : _entities) {
            if (auto* light = dynamic_cast<Light*>(entity.get())) {
                LightData data{};
                data.position = light->transform().position();
                data.colour = light->colour();
                data.intensity = light->intensity();
                data.type = light->type();

                _lightData.push_back(data);

                light->clearDirty();
            }
        }
    }
} // MEGEngine