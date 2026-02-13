#include "MEGEngine/shader_manager.h"
#include "MEGEngine/utils/log.h"
#include "MEGEngine/settings.h"

namespace MEGEngine {
    // initialise static members
    std::unordered_map<std::string, std::unique_ptr<Shader>> ShaderManager::_shaders;
    std::vector<std::string> ShaderManager::_defaultShaders = {
        "defaultLit",
        "light"
    };

    Shader* ShaderManager::getShader(const std::string& name) {
        // search list of already compiled shaders
        if (_shaders.find(name) != _shaders.end()) {
            return _shaders[name].get();
        }

        // not already compiled, search default shader list
        for (const auto& shaderName : _defaultShaders) {
            if (shaderName == name) {
                std::string vertexFile = settings.general().shaderDirectory + "/" + name + "/" + name + ".vert";
                std::string fragmentFile = settings.general().shaderDirectory + "/" + name + "/" + name + ".frag";
                std::unique_ptr<Shader> shader = std::make_unique<Shader>(vertexFile.c_str(), fragmentFile.c_str());
                _shaders[name] = std::move(shader);
                return _shaders[name].get();
            }
        }

        // If reached this point, shader hasn't been found
        Log(LogLevel::ERR, "Get shader failed: " + name + " does not exist. Create shader first");
        return nullptr;
    }

    Shader* ShaderManager::createShader(const std::string& name, const char* vertexFile, const char* fragmentFile) {
        std::unique_ptr<Shader> shader = std::make_unique<Shader>(vertexFile, fragmentFile);
        _shaders[name] = std::move(shader);

        return _shaders[name].get();
    }

    void ShaderManager::cleanUp() {

    }
} // MEGEngine