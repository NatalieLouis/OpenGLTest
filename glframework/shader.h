#pragma once
#include <string>
#include "core.h"

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();
	void end();
	void setFloat(const std::string& name,float value);
	void setVector3(const std::string& name, float x, float y, float z);
	void setVector3(const std::string& name, const float* values);
	void setInt(const std::string& name, int value);
private:
	enum class Type {
		COMPILE = 0,
		LINK
	};
	void checkShaderErrors(GLuint target, Type type);
private:
	GLuint mProgram{ 0 };
};