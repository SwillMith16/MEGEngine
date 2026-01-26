#include "scene.h"
#include "camera.h"

namespace MEGEngine {
    Scene::Scene() : _camera(std::make_unique<Camera>(Camera(800, 800, {0, 0, 0}))) {}

    const std::vector<std::unique_ptr<Entity>>& Scene::entities() const {
        return _entities;
    }

    Entity &Scene::createEntity() {
        _entities.push_back(std::make_unique<Entity>());
        return *_entities.back();
    }

    Camera& Scene::camera() const {
        return *_camera;
    }

    void Scene::update(float dt) {
        for (auto& entity : _entities) {
            entity->onUpdate(dt);
        }
    }
} // MEGEngine