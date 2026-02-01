#include "GLAD/glad.h"

#include "MEGEngine/renderer.h"
#include "MEGEngine/camera.h"
#include "MEGEngine/material.h"
#include "MEGEngine/mesh.h"
#include "MEGEngine/shader.h"
#include "MEGEngine/scene.h"
#include "MEGEngine/texture.h"

#include "MEGEngine/math/glm_conversions.h"

#include "MEGEngine/utils/log.h"

namespace MEGEngine {
    struct Renderer::RenderGroup {
        std::shared_ptr<Shader> shader = nullptr;
        std::vector<Entity*> entities;
    };

    void Renderer::init() {
        if (!gladLoadGL())
            throw std::runtime_error("GLAD initialization failed");

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        _initialised = true;
    }

    void Renderer::render(const Scene& scene) {
        if (!_initialised)
            return;

        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        std::vector<RenderGroup> renderQueue;

        for (auto& entity : scene.entities()) {
            if (entity->meshRenderer()) { // loop through render groups to store entities in order of shader
                if (renderQueue.empty()) {
                    RenderGroup newGroup;
                    newGroup.shader = entity->meshRenderer()->material()->shader();
                    renderQueue.push_back(newGroup);
                }

                for (int i = 0; i < renderQueue.size(); i++) {
                    if (entity->meshRenderer()->material()->shader().get()->ID() == renderQueue[i].shader.get()->ID()) {
                        renderQueue[i].entities.push_back(entity.get());
                    }
                    else if (i == renderQueue.size() - 1) {
                        RenderGroup newGroup;
                        newGroup.shader = entity->meshRenderer()->material()->shader();
                        newGroup.entities.push_back(entity.get());
                        renderQueue.push_back(newGroup);
                    }
                }
            }
        }

        for (RenderGroup& group : renderQueue) {
            glUseProgram(group.shader->ID());
            for (auto entity : group.entities) {
                draw(*entity, scene);
            }
        }
    }

    void Renderer::draw(Entity& entity, const Scene& scene) {
        if (!entity.meshRenderer()->material()->shader()) {
            Log(LogLevel::WRN, "Attempt to draw failed. Shader is null");
            return;
        }

        entity.meshRenderer()->material()->bind();
        entity.meshRenderer()->mesh()->bind();

        // Keep track of how many of each type of textures we have
        unsigned int numDiffuse = 0;
        unsigned int numSpecular = 0;

        for (unsigned int i = 0; i < entity.meshRenderer()->material()->textures().size(); i++)
        {
            std::string num;
            std::string type = entity.meshRenderer()->material()->textures()[i].type;
            if (type == "diffuse")
            {
                num = std::to_string(numDiffuse++);
            }
            else if (type == "specular")
            {
                num = std::to_string(numSpecular++);
            }
            entity.meshRenderer()->material()->textures()[i].texUnit(*entity.meshRenderer()->material()->shader().get(), (type + num).c_str(), i);
            entity.meshRenderer()->material()->textures()[i].bind();
        }
        entity.meshRenderer()->material()->shader()->setUniform("camPos", scene.camera().transform().position());
        scene.camera().matrix(*entity.meshRenderer()->material()->shader().get(), "camMatrix");

        // Create matrices
        Mat4 trans = Mat4::translation(entity.transform().position());
        Mat4 rot = entity.transform().rotation().toMatrix();
        Mat4 sca = Mat4::scale(entity.transform().scale());

        // Push the matrices to the vertex shader
        Mat4 modelMatrix = entity.transform().modelMatrix();
        entity.meshRenderer()->material()->shader()->setUniform("model",  modelMatrix);
        entity.meshRenderer()->material()->shader()->setUniform("translation", trans);
        entity.meshRenderer()->material()->shader()->setUniform("rotation", rot);
        entity.meshRenderer()->material()->shader()->setUniform("scale", sca);

        entity.meshRenderer()->material()->shader()->setUniform("lightColour", scene.lightData()[0].colour);
        if (auto* light = dynamic_cast<Light*>(&entity)) {
            entity.meshRenderer()->material()->shader()->setUniform("translation", scene.lightData()[0].position);
        } else {
            entity.meshRenderer()->material()->shader()->setUniform("lightPosition", scene.lightData()[0].colour);
        }


        // Draw the actual mesh
        glDrawElements(GL_TRIANGLES, entity.meshRenderer()->mesh()->numIndices(), GL_UNSIGNED_INT, 0);
    }
} // MEGEngine