#ifndef MEGENGINEPROJECT_MODEL_LOADER_H
#define MEGENGINEPROJECT_MODEL_LOADER_H

#include <vector>

#include "MEGEngine/common.h"

#include "MEGEngine/math/vec2.h"
#include "MEGEngine/math/vec3.h"
#include "MEGEngine/math/vec4.h"
#include "MEGEngine/math/mat4.h"

namespace MEGEngine {
    class Entity;
    struct JSONImpl;
    class ENGINE_API ModelLoader {
    public:
        static ModelLoader& instance();
        void loadModelFromFile(Entity& model, const char* file);
        void loadModelFromData(Entity& model, const std::vector<class Vertex>& vertices, const std::vector<unsigned int>& indices);



    private:
        ModelLoader();

        const char* _file = nullptr;
        std::vector<unsigned char> _data;
        std::unique_ptr<JSONImpl> _impl;

        std::vector<std::string> _loadedTexName;
        std::vector<class Texture> _loadedTex;

        class MeshRenderer loadMeshRenderer(unsigned int indMesh);

        void traverseNode(Entity& model, unsigned int nextNode, Mat4 matrix = Mat4(1.0f));

        std::vector<unsigned char> getData();
        std::vector<Texture> getTextures();

        std::vector<struct Vertex> assembleVertices(std::vector<Vec3> positions, std::vector<Vec3> normals, std::vector<Vec2> texUVs);

        std::vector<Vec2> groupFloatsVec2(std::vector<float> floatVec);
        std::vector<Vec3> groupFloatsVec3(std::vector<float> floatVec);
        std::vector<Vec4> groupFloatsVec4(std::vector<float> floatVec);
    };

    inline ENGINE_API ModelLoader& modelLoader = ModelLoader::instance();
} // MEGEngine

#endif //MEGENGINEPROJECT_MODEL_LOADER_H