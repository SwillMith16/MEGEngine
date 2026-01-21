#ifndef TEXTURE_H
#define TEXTURE_H

#include "GLAD/glad.h"

#include "common.h"
#include "shader.h"

namespace MEGEngine {
	class ENGINE_API Texture {
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