#include <fstream>
#include <iostream>

#include "shader.h"

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


		ID = glCreateProgram();
		// create shader program and attach the shaders to it
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		// wrap-up/link all the shaders together in the program
		glLinkProgram(ID);
		compileErrors(ID, "PROGRAM");

		// now shaders are in the shader program, the shaders themselves are not needed
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::activate() {
		glUseProgram(ID);
	}

	void Shader::del() {
		glDeleteProgram(ID);
	}

	// Checks if the different Shaders have compiled properly
	void Shader::compileErrors(unsigned int shader, const char* type)
	{
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
}