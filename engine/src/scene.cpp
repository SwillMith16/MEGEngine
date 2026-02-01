#include "MEGEngine/scene.h"
#include "MEGEngine/camera.h"

namespace MEGEngine {
    Scene::Scene() : _camera(std::make_unique<Camera>(Camera(1280, 720))) {}

    Scene::Scene(unsigned int width, unsigned int height) : _camera(std::make_unique<Camera>(Camera(width, height))) {}

    const std::vector<std::unique_ptr<Entity>>& Scene::entities() const {
        return _entities;
    }

    const std::vector<LightData>& Scene::lightData() const {
        return _lightData;
    }

    Camera& Scene::camera() const {
        return *_camera;
    }

    void Scene::update(float dt) {
        for (auto& entity : _entities) {
            entity->onUpdate(dt);
        }

        updateLights();

        _camera->updateMatrix();
    }

    void Scene::updateLights() {
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