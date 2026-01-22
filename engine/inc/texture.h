#ifndef TEXTURE_H
#define TEXTURE_H

#include "common.h"
#include "shader.h"

namespace MEGEngine {
	class ENGINE_API Texture {
	public:
		unsigned int ID;
		const char* type;
		unsigned int unit;
		bool isTextureFlipped = false;

		Texture(const char* image, const char* texType, unsigned int slot);

		void texUnit(Shader& shader, const char* uniform, unsigned int unit);
		void bind();
		void unbind();
		void del();
	};
}


#endif //TEXTURE_H