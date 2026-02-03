#ifndef MEGENGINEPROJECT_MATERIAL_H
#define MEGENGINEPROJECT_MATERIAL_H

#include <memory>
#include <unordered_map>

#include "MEGEngine/common.h"
#include "MEGEngine/texture.h"

namespace MEGEngine {
    class ENGINE_API Material {
    public:
        explicit Material(class Shader* shader);
        Material();

        void bind();

        void setTextures(std::unordered_map<TexType, std::shared_ptr<Texture>> textureList);
        void setTexture(std::shared_ptr<Texture> texture);

        Shader* shader();
        std::unordered_map<TexType, std::shared_ptr<Texture>> textures();
        std::shared_ptr<Texture> texture(TexType type);

    private:
        Shader* _shader;
        std::unordered_map<TexType, std::shared_ptr<Texture>> _textures;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_MATERIAL_H