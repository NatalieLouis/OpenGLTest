#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

GLuint program =0,vao = 0;
void prepareVBO() {
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glDeleteBuffers(1, &vbo);
}
void prepareShader() {
	const char* vertexShaderSource =
		"#version 460 core \n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 color;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"color = aColor;\n"
		"}\0";
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 color;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(color,1.0f);\n"
		"}\n";

	//2创建Shader程序（vs fs)
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//3 为shader程序输入代码

	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

	int success = 0;
	char infoLog[1024];
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		std::cout << "Error compile:" << infoLog << std::endl;
	}

	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
		std::cout << "Error fragment:" << infoLog << std::endl;
	}


	//5 创建一个Program 壳子
	program = glCreateProgram();

	//6 放入壳子中
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	//7 链接
	glLinkProgram(program);

	//8 清理
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	//绑定当前vao
	glBindVertexArray(vao);
	//绘制
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

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
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	auto window = glfwCreateWindow(800, 600, "OpenglLearn", NULL, NULL);
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "Failed to initialize GLAD!" << endl;
		return -1;
	}
	prepareShader();
	prepare();
	while (!glfwWindowShouldClose(window)) {
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}