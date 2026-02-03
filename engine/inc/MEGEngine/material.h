#ifndef MEGENGINEPROJECT_MATERIAL_H
#define MEGENGINEPROJECT_MATERIAL_H

#include <memory>
#include <vector>

#include "MEGEngine/common.h"

namespace MEGEngine {
    class ENGINE_API Material {
    public:
        explicit Material(class Shader* shader);
        Material();

        void bind();

        void setTextureList(std::vector<class Texture> textureList);

        Shader* shader();
        std::vector<Texture> textures();

    private:
        Shader* _shader;
        std::vector<Texture> _textures;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_MATERIAL_H