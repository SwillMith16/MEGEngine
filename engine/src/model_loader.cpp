#include "GLM/gtc/type_ptr.hpp"

#include "model_loader.h"
#include "entity.h"
#include "texture.h"
#include "mesh_renderer.h"
#include "mesh.h"
#include "material.h"
#include "texture.h"
#include "shader.h"
#include "vertex.h"

#include "math/glm_conversions.h"

#include "utils/log.h"

namespace MEGEngine {
    ModelLoader& ModelLoader::instance() {
        static ModelLoader instance;
        return instance;
    }

    void ModelLoader::loadModelFromFile(Entity& model, const char *file) {
        Log(LogLevel::DBG, "Loading model from file: %s", file);
        // get full contents of the GLTF model file (follows a JSON format)
        std::string text = get_file_contents(file);

        // With data parsed into a JSON object, we can access the data without manually reading and modifying strings
        _json = json::parse(text);

        // store the raw data as bytes
        this->_file = file;
        _data = getData();

        // traverse the node tree, to find children nodes and dependent matrices
        traverseNode(model, 0);
    }

    void ModelLoader::traverseNode(Entity& model, unsigned int nodeIndex, Mat4 matrix) {
        Log(LogLevel::DBG, "Processing model node index: %u", nodeIndex);
        json node = _json["nodes"][nodeIndex];

        // If this node has a translation, get it
        Vec3 translation = Vec3(0, 0, 0);
        if (node.find("translation") != node.end()) {
            float transValues[3];
            for (unsigned int i = 0; i < node["translation"].size(); i++)
                transValues[i] = (node["translation"][i]);
            translation = Vec3(transValues[0], transValues[1], transValues[2]);
        }

        // If this node has a rotation, get it
        Quat rotation = Quat(0, 0, 0, 1);
        if (node.find("rotation") != node.end()) {
            float rotValues[4];
            for (unsigned int i = 0; i < node["rotation"].size(); i++)
                rotValues[i] = (node["rotation"][i]);
            rotation = Quat(rotValues[0], rotValues[1], rotValues[2], rotValues[3]);
        }

        // If this node has a scale, get it
        Vec3 scale = Vec3(1, 1, 1);
        if (node.find("scale") != node.end()) {
            float scaleValues[3];
            for (unsigned int i = 0; i < node["scale"].size(); i++)
                scaleValues[i] = (node["scale"][i]);
            scale = Vec3(scaleValues[0], scaleValues[1], scaleValues[2]);
        }

        // If this node has a matrix, get it
        Mat4 matNode = Mat4(1.0f);
        if (node.find("matrix") != node.end())
        {
            float matValues[16];
            for (unsigned int i = 0; i < node["matrix"].size(); i++)
                matValues[i] = (node["matrix"][i]);
            matNode = Private::fromGlmMat4(glm::make_mat4(matValues));
        }

        // Use translation, rotation, and scale as matrices
        Mat4 trans = Mat4::translation(translation);
        Mat4 rot = rotation.toMatrix();
        Mat4 sca = Mat4::scale(scale);

        /*
         * Multiply all matrices together.
         * This carries forward the previous calculated matrix, so each node in the tree is dependent on the last.
         * Important for models that contains several meshes, so each mesh is positioned correctly relative to the others.
         * Without this, each mesh will be positioned on top of/inside one another.
        */
        Mat4 matNextNode = matrix * matNode * trans * rot * sca;

        // Check if the node contains a mesh and if it does load it
        if (node.find("mesh") != node.end())
        {
            model.setMeshRenderer(std::make_shared<MeshRenderer>(loadMeshRenderer(node["mesh"])));
        }

        // Check if the node has children, and if it does, apply this function to them with the matNextNode
        if (node.find("children") != node.end())
        {
            for (unsigned int i = 0; i < node["children"].size(); i++) {
                Entity child = Entity();
                model.addChild(child);
                traverseNode(child, node["children"][i], matNextNode);
            }
        }
    }


    MeshRenderer ModelLoader::loadMeshRenderer(unsigned int indMesh) {
        // Get all accessor indices
        unsigned int posAccInd = _json["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
        unsigned int normalAccInd = _json["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
        unsigned int texAccInd = _json["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
        unsigned int indAccInd = _json["meshes"][indMesh]["primitives"][0]["indices"];

        // Use accessor indices to get all vertices components
        std::vector<float> posVec = getFloats(_json["accessors"][posAccInd]);
        std::vector<Vec3> positions = groupFloatsVec3(posVec);
        std::vector<float> normalVec = getFloats(_json["accessors"][normalAccInd]);
        std::vector<Vec3> normals = groupFloatsVec3(normalVec);
        std::vector<float> texVec = getFloats(_json["accessors"][texAccInd]);
        std::vector<Vec2> texUVs = groupFloatsVec2(texVec);

        // Combine all the vertex components and also get the indices and textures
        std::vector<Vertex> vertices = assembleVertices(positions, normals, texUVs);
        std::vector<unsigned int> indices = getIndices(_json["accessors"][indAccInd]);
        std::vector<Texture> textures = getTextures();

        // Combine the vertices, indices into a mesh, and texture, shader into material
        Material material(std::make_shared<Shader>());
        material.setTextureList(textures);
        Mesh mesh(vertices, indices);
        MeshRenderer mr(std::make_shared<Mesh>(mesh), std::make_shared<Material>(material));
        return mr;
    }

    std::vector<unsigned char> ModelLoader::getData() {
        // Create a place to store the raw text, and get the uri of the .bin file
        std::string bytesText;
        std::string uri = _json["buffers"][0]["uri"];

        // Store raw text data into bytesText
        std::string fileStr = std::string(_file);
        std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
        bytesText = get_file_contents((fileDirectory + uri).c_str());

        // Transform the raw text data into bytes and put them in a vector
        std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
        return data;
    }

    std::vector<float> ModelLoader::getFloats(json accessor) {
        std::vector<float> floatVec;

        // Get properties from the accessor
        unsigned int buffViewInd = accessor.value("bufferView", 1);
        unsigned int count = accessor["count"];
        unsigned int accByteOffset = accessor.value("byteOffset", 0);
        std::string type = accessor["type"];

        // Get properties from the bufferView
        json bufferView = _json["bufferViews"][buffViewInd];
        unsigned int byteOffset = bufferView["byteOffset"];

        // Interpret the type and store it into numPerVert
        unsigned int numPerVert;
        if (type == "SCALAR") numPerVert = 1;
        else if (type == "VEC2") numPerVert = 2;
        else if (type == "VEC3") numPerVert = 3;
        else if (type == "VEC4") numPerVert = 4;
        else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

        // Go over all the bytes in the data at the correct place using the properties from above
        unsigned int beginningOfData = byteOffset + accByteOffset;
        unsigned int lengthOfData = count * 4 * numPerVert;
        for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i += 4)
        {
            unsigned char bytes[] = { _data[i], _data[i + 1], _data[i + 2], _data[i + 3] };
            float value;
            std::memcpy(&value, bytes, sizeof(float));
            floatVec.push_back(value);
        }

        return floatVec;
    }

    std::vector <unsigned int> ModelLoader::getIndices(json accessor) {
        std::vector<unsigned int> indices;

        // Get properties from the accessor
        unsigned int buffViewInd = accessor.value("bufferView", 0);
        unsigned int count = accessor["count"];
        unsigned int accByteOffset = accessor.value("byteOffset", 0);
        unsigned int componentType = accessor["componentType"];

        // Get properties from the bufferView
        json bufferView = _json["bufferViews"][buffViewInd];
        unsigned int byteOffset = bufferView["byteOffset"];

        // Get indices with regards to their type: unsigned int, unsigned short, or short
        unsigned int beginningOfData = byteOffset + accByteOffset;
        if (componentType == 5125)
        {
            for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i += 4)
            {
                unsigned char bytes[] = { _data[i], _data[i + 1], _data[i + 2], _data[i + 3] };
                unsigned int value;
                std::memcpy(&value, bytes, sizeof(unsigned int));
                indices.push_back(static_cast<unsigned int>(value));
            }
        }
        else if (componentType == 5123)
        {
            for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i += 2)
            {
                unsigned char bytes[] = { _data[i], _data[i + 1] };
                unsigned short value;
                std::memcpy(&value, bytes, sizeof(unsigned short));
                indices.push_back(static_cast<unsigned int>(value));
            }
        }
        else if (componentType == 5122)
        {
            for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i += 2)
            {
                unsigned char bytes[] = { _data[i], _data[i + 1] };
                short value;
                std::memcpy(&value, bytes, sizeof(short));
                indices.push_back(static_cast<unsigned int>(value));
            }
        }

        return indices;
    }

    std::vector<Texture> ModelLoader::getTextures() {
        std::vector<Texture> textures;

        std::string fileStr = std::string(_file);
        std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

        // Go over all images
        for (unsigned int i = 0; i < _json["images"].size(); i++)
        {
            // uri of current texture
            std::string texPath = _json["images"][i]["uri"];

            // Check if the texture has already been loaded
            bool skip = false;
            for (unsigned int j = 0; j < _loadedTexName.size(); j++)
            {
                if (_loadedTexName[j] == texPath)
                {
                    textures.push_back(_loadedTex[j]);
                    skip = true;
                    break;
                }
            }

            // If the texture has been loaded, skip this
            if (!skip)
            {
                // Load diffuse texture
                if (texPath.find("baseColor") != std::string::npos)
                {
                    Texture diffuse = Texture((fileDirectory + texPath).c_str(), "diffuse", _loadedTex.size());
                    textures.push_back(diffuse);
                    _loadedTex.push_back(diffuse);
                    _loadedTexName.push_back(texPath);
                }
                // Load specular texture
                else if (texPath.find("metallicRoughness") != std::string::npos)
                {
                    Texture specular = Texture((fileDirectory + texPath).c_str(), "specular", _loadedTex.size());
                    textures.push_back(specular);
                    _loadedTex.push_back(specular);
                    _loadedTexName.push_back(texPath);
                }
            }
        }

        return textures;
    }

    std::vector<Vertex> ModelLoader::assembleVertices(std::vector<Vec3> positions, std::vector<Vec3> normals, std::vector<Vec2> texUVs) {
        std::vector<Vertex> vertices;
        for (int i = 0; i < positions.size(); i++)
        {
            vertices.emplace_back(positions[i], normals[i], Vec3(1.0f, 1.0f, 1.0f), texUVs[i]);
        }
        return vertices;
    }


    std::vector<Vec2> ModelLoader::groupFloatsVec2(std::vector<float> floatVec) {
        std::vector<Vec2> vectors;
        for (int i = 0; i < floatVec.size(); i+=2) {
            vectors.emplace_back(floatVec[i], floatVec[i+1]);
        }
        return vectors;
    }

    std::vector<Vec3> ModelLoader::groupFloatsVec3(std::vector<float> floatVec) {
        std::vector<Vec3> vectors;
        for (int i = 0; i < floatVec.size(); i+=3) {
            vectors.emplace_back(floatVec[i], floatVec[i+1], floatVec[i+2]);
        }
        return vectors;
    }

    std::vector<Vec4> ModelLoader::groupFloatsVec4(std::vector<float> floatVec) {
        std::vector<Vec4> vectors;
        for (int i = 0; i < floatVec.size(); i+=4) {
            vectors.emplace_back(floatVec[i], floatVec[i+1], floatVec[i+2], floatVec[i+3]);
        }
        return vectors;
    }
} // MEGEngine