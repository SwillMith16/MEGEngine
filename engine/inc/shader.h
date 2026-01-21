#ifndef SHADER_H
#define SHADER_H

#include <iostream>

#include "GLAD/glad.h"
#include "GLM/gtc/type_ptr.hpp"
#include <string>
#include <sstream>

#include "common.h"
#include "math/vec3.h"
#include "math/vec2.h"

namespace MEGEngine {
	std::string get_file_contents(const char* filename);

	class ENGINE_API Shader {
	public:
		GLuint ID;
		Shader(const char* vertexFile, const char* fragmentFile);

		void activate();
		void del();

		template<typename T>
		void setUniform(const char* name, T& value) {
			if constexpr (std::is_same<T, GLfloat>::value)
				glUniform1f(glGetUniformLocation(ID, name), value);
			else if constexpr (std::is_same<T, GLuint>::value)
				glUniform1i(glGetUniformLocation(ID, name), value);
			else if constexpr (std::is_same<T, glm::vec2>::value || std::is_same<T, Vec2>::value)
				glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
			else if constexpr (std::is_same<T, glm::vec3>::value || std::is_same<T, Vec3>::value)
				glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
			else if constexpr (std::is_same<T, glm::vec4>::value)
				glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
			else if constexpr (std::is_same<T, glm::mat2>::value)
				glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
			else if constexpr (std::is_same<T, glm::mat3>::value)
				glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
			else if constexpr (std::is_same<T, glm::mat4>::value)
				glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
			else
				std::cout << "Invalid uniform type provided" << std::endl;
		}
	private:
		void compileErrors(unsigned int shader, const char* type);
	};
}

#endif //SHADER_H