#include "MEGEngine/material.h"

#include "MEGEngine/shader.h"
#include "MEGEngine/shader_manager.h"
#include "MEGEngine/texture.h"
#include "MEGEngine/utils/log.h"

namespace MEGEngine {
    Material::Material(Shader* shader) : _shader(shader) {}
    Material::Material() : _shader(ShaderManager::getShader("defaultLit")) {}

    void Material::bind() {
        if (_shader) {
            _shader->activate();

            _shader->setUniform("useTex", 0);
            _shader->setUniform("materialColour", _colour);

            // for each texture type, check if one is in texture list. If yes, give it to the shader
            for (int typeInt = 0; typeInt < static_cast<int>(TexType::END); typeInt++) {
                TexType type = static_cast<TexType>(typeInt);
                if (_textures.find(type) != _textures.end()) {
                    _shader->setUniform("useTex", 1);
                    _shader->setUniform("diffuse0", _textures.at(type)->ID); // TODO: overwrites if multiple textures
                }
            }
        } else {
            Log(LogLevel::ERR, "Material binding failed: shader is null");
        }
    }


    void Material::setTextures(std::unordered_map<TexType, std::shared_ptr<Texture>> textureList) {
        _textures = std::move(textureList);
    }

    void Material::setTexture(std::shared_ptr<Texture> texture) {
        TexType type = texture->type;
        if (_textures.find(type) != _textures.end()) {
            _textures.at(type) = texture;
        } else {
            _textures.insert(std::make_pair(type, texture));
        }
    }

    Shader* Material::shader() {
        return _shader;
    }

    std::unordered_map<TexType, std::shared_ptr<Texture>> Material::textures() {
        return _textures;
    }

    std::shared_ptr<Texture> Material::texture(TexType type) {
        if (_textures.find(type) != _textures.end()) {
            return _textures.at(type);
        }
        return nullptr; // texture of specified type is not in the list
    }

    void Material::setColour(Colour colour) {
        _colour = colour;
    }

    Colour Material::colour() {
        return _colour;
    }
} // MEGEngine