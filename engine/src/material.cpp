#include "MEGEngine/material.h"

#include "MEGEngine/shader.h"
#include "MEGEngine/shader_manager.h"
#include "MEGEngine/texture.h"
#include "MEGEngine/utils/log.h"

namespace MEGEngine {
    Material::Material(std::shared_ptr<class Shader> shader) : _shader(std::move(shader)) {}
    Material::Material() : _shader(ShaderManager::getShader("defaultLit")) {}

    void Material::bind() {
        if (_shader) {
            _shader->activate();
            _shader->setUniform("diffuse0", _textures[0].ID);
        } else {
            Log(LogLevel::WRN, "Attempt to bind material failed. Shader is null");
        }
    }


    void Material::setTextureList(std::vector<Texture> textureList) {
        _textures = std::move(textureList);
    }

    std::shared_ptr<Shader> Material::shader() {
        return _shader;
    }


    std::vector<Texture> Material::textures() {
        return _textures;
    }
} // MEGEngine