#pragma once
#include <string>
#include "core.h"

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();
	void end();

private:
	enum class Type {
		COMPILE = 0,
		LINK
	};
	void checkShaderErrors(GLuint target, Type type);
private:
	GLuint mProgram{ 0 };
};