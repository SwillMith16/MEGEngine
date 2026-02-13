#ifndef TEXTURE_H
#define TEXTURE_H

#include "MEGEngine/common.h"

namespace MEGEngine {
	enum class TexType {
		ALBEDO = 0,
		SPECULAR,
		NORMAL,
		EMISSION,
		END
	};

	class ENGINE_API Texture {
	public:
		unsigned int ID;
		TexType type;
		unsigned int unit;
		bool isTextureFlipped = false;

		Texture(const char* image, TexType texType, unsigned int slot);

		void texUnit(class Shader& shader, const char* uniform, unsigned int unit);
		void bind();
		void unbind();
		void del();
	};
}


#endif //TEXTURE_H