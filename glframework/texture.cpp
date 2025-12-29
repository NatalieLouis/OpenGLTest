#include "texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"


Texture::Texture(const char* path, GLint active) {
	mUint = active;
	int channels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path, &mWidth, &mHeight, &channels, STBI_rgb_alpha);
	if (!data) {
		std::cerr << "Failed to load texture\n";
	}

	glGenTextures(1, &mTexture);

	glActiveTexture(GL_TEXTURE0+mUint);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	//¿ªÆôÏÔ´æ
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//v
}

Texture::~Texture() {
	if (mTexture != 0) {
		glDeleteTextures(1, &mTexture);
	}
}

void Texture::bind() {
	glActiveTexture(GL_TEXTURE0 + mUint);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}