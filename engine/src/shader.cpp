#include <fstream>
#include <iostream>

#include "GLAD/glad.h"
#include "GLM/gtc/type_ptr.hpp"

#include "MEGEngine/shader.h"

#include "MEGEngine/math/glm_conversions.h"
#include "MEGEngine/math/vec2.h"
#include "MEGEngine/math/vec3.h"
#include "MEGEngine/math/vec4.h"
#include "MEGEngine/math/mat4.h"
#include "MEGEngine/colour.h"

namespace MEGEngine {
	// Reads a text file and outputs a string with everything in the text file
	std::string get_file_contents(const char* filename) {
		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Failed to open file for reading: " + std::string(filename));
		}
		std::stringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}

	unsigned int Shader::ID() {
		return _id;
	}

	Shader::Shader(const char* vertexFile, const char* fragmentFile) {
		// get vertex shader code
		std::string vertexCode;
		try {
			vertexCode = get_file_contents(vertexFile);
		} catch (int e) {
			std::cerr << "ERROR Failed to get vertex shader file. Code " << e << std::endl;
		}

		// get fragment shader code
		std::string fragmentCode;
		try {
			fragmentCode = get_file_contents(fragmentFile);
		} catch (int e) {
			std::cerr << "ERROR Failed to get fragment shader file. Code " << e << std::endl;
		}

		const char* vertexSource = vertexCode.c_str();
		const char* fragmentSource = fragmentCode.c_str();


		// create a vertex shader object
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		// attach the vertex shader source code to the object
		glShaderSource(vertexShader, 1, &vertexSource, nullptr );
		// compile the source into machine code for the GPU
		glCompileShader(vertexShader);
		// Checks if Shader compiled succesfully
		compileErrors(vertexShader, "VERTEX");

		// same again for fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, nullptr );
		glCompileShader(fragmentShader);
		compileErrors(fragmentShader, "FRAGMENT");


		_id = glCreateProgram();
		// create shader program and attach the shaders to it
		glAttachShader(_id, vertexShader);
		glAttachShader(_id, fragmentShader);
		// wrap-up/link all the shaders together in the program
		glLinkProgram(_id);
		compileErrors(_id, "PROGRAM");

		// now shaders are in the shader program, the shaders themselves are not needed
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::activate() {
		glUseProgram(_id);
	}

	void Shader::del() {
		glDeleteProgram(_id);
	}

	// Checks if the different Shaders have compiled properly
	void Shader::compileErrors(unsigned int shader, const char* type) {
		// Stores status of compilation
		GLint hasCompiled;
		// Character array to store error message in
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
			}
		}
	}

	template<typename T>
	void Shader::setUniform(const char* name, const T& value) {
		activate();
		if constexpr (std::is_same<T, float>::value)
			glUniform1f(glGetUniformLocation(_id, name), value);
		else if constexpr (std::is_same<T, int>::value)
			glUniform1i(glGetUniformLocation(_id, name), value);
		else if constexpr (std::is_same<T, unsigned int>::value)
			glUniform1ui(glGetUniformLocation(_id, name), value);
		else if constexpr (std::is_same<T, Vec2>::value)
			glUniform2f(glGetUniformLocation(_id, name), value.x, value.y);
		else if constexpr (std::is_same<T, Vec3>::value)
			glUniform3f(glGetUniformLocation(_id, name), value.x, value.y, value.z);
		else if constexpr (std::is_same<T, Vec4>::value)
			glUniform4f(glGetUniformLocation(_id, name), value.x, value.y, value.z, value.w);
		else if constexpr (std::is_same<T, Colour>::value)
			glUniform4f(glGetUniformLocation(_id, name), value.r, value.g, value.b, value.a);
		else if constexpr (std::is_same<T, Mat4>::value)
			glUniformMatrix4fv(glGetUniformLocation(_id, name), 1, GL_FALSE, glm::value_ptr(Private::toGlmMat4(value)));
		else
			std::cout << "Invalid uniform type provided" << std::endl;
	}

	template void Shader::setUniform<float>(const char* name, const float& value);
	template void Shader::setUniform<int>(const char* name, const int& value);
	template void Shader::setUniform<unsigned int>(const char* name, const unsigned int& value);
	template void Shader::setUniform<Vec2>(const char* name, const Vec2& value);
	template void Shader::setUniform<Vec3>(const char* name, const Vec3& value);
	template void Shader::setUniform<Vec4>(const char* name, const Vec4& value);
	template void Shader::setUniform<Colour>(const char* name, const Colour& value);
	template void Shader::setUniform<Mat4>(const char* name, const Mat4& value);
}