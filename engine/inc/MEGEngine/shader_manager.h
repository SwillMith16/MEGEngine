#ifndef MEGENGINEPROJECT_SHADER_MANAGER_H
#define MEGENGINEPROJECT_SHADER_MANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "MEGEngine/common.h"
#include "MEGEngine/shader.h"

namespace MEGEngine {
    class ENGINE_API ShaderManager {
    public:
        static Shader* getShader(const std::string& name);
        static Shader* createShader(const std::string& name, const char* vertexFile, const char* fragmentFile);
        static void cleanUp();

    private:
        static std::unordered_map<std::string, std::unique_ptr<Shader>> _shaders;
        static std::vector<std::string> _defaultShaders;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_SHADER_MANAGER_H