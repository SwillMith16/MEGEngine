#include "material.h"

#include <utility>

#include "shader.h"
#include "texture.h"
#include "GLAD/glad.h"

namespace MEGEngine {
    Material::Material(std::shared_ptr<class Shader> shader) : _shader(std::move(shader)) {}

    void Material::bind() {
        _shader->activate();
        _shader->setUniform("diffuse0", _textures[0].ID);
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