#include "application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Application* Application::mInstance = nullptr;

Application* Application::getInstance() {
	if (mInstance == nullptr) {
		mInstance = new Application();
	}
	return mInstance;
}
Application::Application() {
	
}

//uint32_t Application::getWidth() { return this->mWidth; }
//uint32_t Application::getHeight() { return this->mHeight; }

bool Application::init(const int& width, const int& height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	mWindow = glfwCreateWindow(width, height, "OpenglLearn", NULL, NULL);
	if (mWindow == nullptr) {
		return false;
	}
	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}

}
bool Application::update() {
	if (glfwWindowShouldClose(mWindow))return false;
	glfwPollEvents();
	glfwSwapBuffers(mWindow);
	return true;
	
}
void Application::destroy() {
	glfwTerminate();
}

Application::~Application(){}