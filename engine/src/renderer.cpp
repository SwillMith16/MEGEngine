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
                drawMesh(*entity->meshRenderer(), entity->transform(), scene.camera());
            }
        }
    }

    void Renderer::drawMesh(const MeshRenderer& mr, const Transform& transform, const Camera& camera) {
        if (!mr.material()->shader()) {
            Log(LogLevel::WRN, "Attempt to draw failed. Shader is null");
            return;
        }

        mr.material()->bind();
        mr.mesh()->bind();

        // Keep track of how many of each type of textures we have
        unsigned int numDiffuse = 0;
        unsigned int numSpecular = 0;

        for (unsigned int i = 0; i < mr.material()->textures().size(); i++)
        {
            std::string num;
            std::string type = mr.material()->textures()[i].type;
            if (type == "diffuse")
            {
                num = std::to_string(numDiffuse++);
            }
            else if (type == "specular")
            {
                num = std::to_string(numSpecular++);
            }
            mr.material()->textures()[i].texUnit(*mr.material()->shader().get(), (type + num).c_str(), i);
            mr.material()->textures()[i].bind();
        }
        mr.material()->shader()->setUniform("camPos", camera.transform().position());
        camera.matrix(*mr.material()->shader().get(), "camMatrix");

        // Create matrices
        Mat4 trans = Mat4::translation(transform.position());
        Mat4 rot = transform.rotation().toMatrix();
        Mat4 sca = Mat4::scale(transform.scale());

        // Push the matrices to the vertex shader
        Mat4 modelMatrix = transform.modelMatrix();
        mr.material()->shader()->setUniform("model",  modelMatrix);
        mr.material()->shader()->setUniform("translation", trans);
        mr.material()->shader()->setUniform("rotation", rot);
        mr.material()->shader()->setUniform("scale", sca);

        // Draw the actual mesh
        glDrawElements(GL_TRIANGLES, mr.mesh()->numIndices(), GL_UNSIGNED_INT, 0);


    }
} // MEGEngine