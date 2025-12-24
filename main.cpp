#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
void prepareVBO() {
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glDeleteBuffers(1, &vbo);
}
void prepare() {
	float vertices[] = {
		-0.5,-0.5,0,
		0.5,-0.5,0,
		0,0.5,0
	};
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
}
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	auto window = glfwCreateWindow(800, 600, "OpenglLearn", NULL, NULL);
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}