#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <sstream>

#include "common.h"


namespace MEGEngine {
	std::string get_file_contents(const char* filename);

	class ENGINE_API Shader {
	public:
		unsigned int ID;
		Shader(const char* vertexFile, const char* fragmentFile);

		void activate();
		void del();

		// defined in shader_priv.h
		template<typename T>
		void setUniform(const char* name, T& value);

	private:
		void compileErrors(unsigned int shader, const char* type);
	};
}

#endif //SHADER_H