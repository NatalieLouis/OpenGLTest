#include"shader.h"

#include <string>
#include<fstream>
#include<sstream>
#include<iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderSteam, fShaderStream;
		vShaderSteam << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderSteam.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout <<"load glsl error:"<< e.what() << std::endl;
	}
	//1 glsl代码
	const char* vertexShaderSource = vertexCode.c_str();//和vertexCode.data()
	const char* fragmentShaderSource = fragmentCode.c_str();

	//2创建Shader程序（vs fs)
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//3 为shader程序输入代码
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

	glCompileShader(vertex);
	checkShaderErrors(vertex, Type::COMPILE);

	glCompileShader(fragment);
	checkShaderErrors(fragment, Type::COMPILE);


	//5 创建一个Program 壳子
	mProgram = glCreateProgram();

	//6 放入壳子中
	glAttachShader(mProgram, vertex);
	glAttachShader(mProgram, fragment);

	//7 链接
	glLinkProgram(mProgram);
	checkShaderErrors(mProgram, Type::LINK);

	//8 清理
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::checkShaderErrors(GLuint target, Type type) {
	int success = 0;
	char infoLog[1024];
	if (type == Type::COMPILE) {
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(target, 1024, NULL, infoLog);
			std::cout << "Complie Errors:" << infoLog << std::endl;
		}
	}
	else if(type ==Type::LINK) {
		glGetProgramiv(target,GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(target, 1024, NULL, infoLog);
			std::cout << "Link Errors:" << infoLog << std::endl;
		}
	}
	else {
		std::cout << "Not Supported Type to Check" << std::endl;
	}
}

Shader::~Shader(){}

void Shader::begin() {
	glUseProgram(mProgram);
}

void Shader::end() {
	glUseProgram(0);
}