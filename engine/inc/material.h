#ifndef MEGENGINEPROJECT_MATERIAL_H
#define MEGENGINEPROJECT_MATERIAL_H

#include <memory>
#include <vector>

#include "common.h"

namespace MEGEngine {
    class ENGINE_API Material {
    public:
        explicit Material(std::shared_ptr<class Shader> shader);

        void bind();

        void setTextureList(std::vector<class Texture> textureList);

        std::shared_ptr<Shader> shader();

        std::vector<Texture> textures();

    private:
        std::shared_ptr<class Shader> _shader;
        std::vector<Texture> _textures;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_MATERIAL_H