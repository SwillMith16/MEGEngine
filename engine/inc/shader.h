#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <sstream>

#include "common.h"
#include "settings.h"


namespace MEGEngine {
	std::string get_file_contents(const char* filename);

	class ENGINE_API Shader {
	public:
		unsigned int ID;
		Shader(const char* vertexFile = (settings.general().shaderDirectory+"/defaultLit/defaultLit.vert").c_str(), const char* fragmentFile = (settings.general().shaderDirectory+"/defaultLit/defaultLit.frag").c_str());

		void activate();
		void del();

		// defined in shader_priv.h
		template<typename T>
		void setUniform(const char* name, const T& value);

	private:
		void compileErrors(unsigned int shader, const char* type);
	};
}

#endif //SHADER_H