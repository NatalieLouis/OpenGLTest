#include <iostream>
#include "glframework/core.h"
#include "application/application.h"
#include "glframework/shader.h"

using namespace std;

GLuint vao = 0;
Shader* shader = nullptr;
void prepareShader() {
	shader = new Shader("assets/shader/vertex.glsl","assets/shader/fragment.glsl");
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	shader->begin();
	//绑定当前vao
	glBindVertexArray(vao);
	//绘制
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	shader->end();
}
void prepare() {
	float vertices[] = {
		-0.5,-0.5,0,
		0.5,-0.5,0,
		0,0.5,0
	};
	float color[] = {
	 1.0f,0.0f,0.0f,
	 0.0f,1.0f,0.0f,
	 0.0f,0.0f,1.0f
	};
	GLuint vbo , color_vbo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &color_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

	unsigned int indices[] = {
		0,1,2,
	};

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//加入ebo到当前的vao
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);//解绑vao

}
int main() {
	if (!myapp->init()) return -1;

	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	prepareShader();
	prepare();
	while (myapp->update()) {
		render();
	}
	myapp->destroy();
	return 0;
}