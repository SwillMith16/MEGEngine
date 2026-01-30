#include "MEGEngine/shader_manager.h"
#include "MEGEngine/utils/log.h"
#include "MEGEngine/settings.h"

namespace MEGEngine {
    // initialise static members
    std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderManager::_shaders;
    std::vector<std::string> ShaderManager::_defaultShaders = {"defaultLit", "light"};

    std::shared_ptr<Shader> ShaderManager::getShader(std::string name) {

        // search list of already compiled shaders
        if (_shaders.find(name) != _shaders.end()) {
            return _shaders[name];
        }

        // not already compiled, search default shader list
        for (const auto& shaderName : _defaultShaders) {
            if (shaderName == name) {
                std::string vertexFile = settings.general().shaderDirectory + "/" + name + "/" + name + ".vert";
                std::string fragmentFile = settings.general().shaderDirectory + "/" + name + "/" + name + ".frag";
                std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexFile.c_str(), fragmentFile.c_str());
                _shaders[name] = shader;
                return shader;
            }
        }

        // If reached this point, shader hasn't been found
        Log(LogLevel::ERR, "Shader not found: " + name + ". Create shader first");
        return nullptr;
    }

    std::shared_ptr<Shader> ShaderManager::createShader(const std::string& name, const char* vertexFile, const char* fragmentFile) {
        std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexFile, fragmentFile);
        _shaders[name] = shader;

        return shader;
    }

    void ShaderManager::cleanUp() {

    }
} // MEGEngine