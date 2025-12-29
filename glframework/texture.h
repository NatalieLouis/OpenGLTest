#pragma once
#include "core.h"
#include<string>

class Texture {
public:
	Texture(const char* path, GLint active);
	~Texture();
	void bind();
private:
	GLuint mTexture{ 0 };
	int mWidth{ 0 };
	int mHeight{ 0 };
	unsigned int mUint{ 0 };
};
