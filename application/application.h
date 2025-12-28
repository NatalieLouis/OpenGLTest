#pragma once
#define myapp Application::getInstance()
class GLFWwindow;
class Application {
public:
	static Application* getInstance();
	bool init(const int& width = 800,const int& height = 600);
	bool update();
	void destroy();
	//uint32_t getWidth();
	//uint32_t getHeight();
	~Application();
private:
	static Application* mInstance;
	Application();

private:
	//uint32_t mWidth{ 0 };
	//uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };
};
