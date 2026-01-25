#ifndef MEGENGINEPROJECT_MODEL_LOADER_H
#define MEGENGINEPROJECT_MODEL_LOADER_H

#include <vector>

#include <JSON/json.hpp>

#include "common.h"

#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"

using json = nlohmann::json;

namespace MEGEngine {
    class Entity;
    class ENGINE_API ModelLoader {
    public:
        static ModelLoader& instance();
        void loadModelFromFile(Entity& model, const char* file); // TODO: Need to add scene as an argument, once scene class is created
        void loadModelFromData(Entity& model, const std::vector<class Vertex>& vertices, const std::vector<unsigned int>& indices); // TODO: same here



    private:
        ModelLoader() = default;

        const char* _file = nullptr;
        std::vector<unsigned char> _data;
        json _json;

        std::vector<std::string> _loadedTexName;
        std::vector<class Texture> _loadedTex;

        class MeshRenderer loadMeshRenderer(unsigned int indMesh);

        void traverseNode(Entity& model, unsigned int nextNode, Mat4 matrix = Mat4(1.0f));

        std::vector<unsigned char> getData();
        std::vector<float> getFloats(json accessor);
        std::vector<unsigned int> getIndices(json accessor);
        std::vector<Texture> getTextures();

        std::vector<struct Vertex> assembleVertices(std::vector<Vec3> positions, std::vector<Vec3> normals, std::vector<Vec2> texUVs);

        std::vector<Vec2> groupFloatsVec2(std::vector<float> floatVec);
        std::vector<Vec3> groupFloatsVec3(std::vector<float> floatVec);
        std::vector<Vec4> groupFloatsVec4(std::vector<float> floatVec);
    };

    inline ENGINE_API ModelLoader& modelLoader = ModelLoader::instance();
} // MEGEngine

#endif //MEGENGINEPROJECT_MODEL_LOADER_H