#include "scene.h"
#include "camera.h"

namespace MEGEngine {
    Scene::Scene() : _camera(std::make_unique<Camera>(Camera(1280, 720))) {}

    Scene::Scene(unsigned int width, unsigned int height) : _camera(std::make_unique<Camera>(Camera(width, height))) {}

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

        _camera->updateMatrix();
    }
} // MEGEngine