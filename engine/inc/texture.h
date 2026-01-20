//
// Created by Will on 07/12/2025.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "GLAD/glad.h"
#include "shader.h"

namespace MEGEngine {
	class Texture {
	public:
		GLuint ID;
		const char* type;
		GLuint unit;
		bool isTextureFlipped = false;

		Texture(const char* image, const char* texType, GLuint slot);

		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		void bind();
		void unbind();
		void del();
	};
}


#endif //TEXTURE_H