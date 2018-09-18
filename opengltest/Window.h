#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>

class Window {
	GLFWwindow* window;

public:
	Window(uint32_t width, uint32_t height);
	~Window();

	void swapBuffers();
	GLFWwindow* getWindow();
	bool isRunning();
};

