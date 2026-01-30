#include <iostream>

#include "GLAD/glad.h"
#include "STB/stb_image.h"

#include "MEGEngine/texture.h"
#include "MEGEngine/shader.h"
#include "MEGEngine/utils/log.h"

namespace MEGEngine {
	Texture::Texture(const char *image, const char *texType, unsigned int slot) {
		// Assigns the type of the texture ot the texture object
		type = texType;

		// Stores the width, height, and the number of color channels of the image
		int widthImg, heightImg, numColCh;
		// Flips the image so it appears right side up
		stbi_set_flip_vertically_on_load(isTextureFlipped);
		// Reads the image from a file and stores it in bytes
		unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

		// Generates an OpenGL texture object
		glGenTextures(1, &ID);
		// Assigns the texture to a Texture Unit
		glActiveTexture(GL_TEXTURE0 + slot);
		unit = slot;
		glBindTexture(GL_TEXTURE_2D, ID);

		// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Assigns the image to the OpenGL Texture object
		switch (numColCh) {
			case 4:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
				Log(LogLevel::DBG, "4 Channel texture image - using GL_RGBA format. Image: %s", image);
				break;
			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
				Log(LogLevel::DBG, "3 Channel texture image - using GL_RGB format. Image: %s", image);
				break;
			case 1:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
				Log(LogLevel::DBG, "1 Channel texture image - using GL_RED format. Image: %s", image);
				break;
			default:
				Log(LogLevel::ERR, "Invalid number of channels in texture image. Must be 4 or 3 or 1. Image: %s", image);
				break;
		}

		// Generates MipMaps
		glGenerateMipmap(GL_TEXTURE_2D);

		// Deletes the image data as it is already in the OpenGL Texture object
		stbi_image_free(bytes);

		// Unbinds the OpenGL Texture object so that it can't accidentally be modified
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	void Texture::texUnit(Shader& shader, const char* uniform, unsigned int unit) {
		// Shader needs to be activated before changing the value of a uniform
		shader.activate();
		// Sets the value of the uniform
		shader.setUniform(uniform, unit);
		// glUniform1i(glGetUniformLocation(shader.ID, uniform), unit);
	}

	void Texture::bind() {
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void Texture::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::del() {
		glDeleteTextures(1, &ID);
	}
}
