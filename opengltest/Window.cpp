#include "stdafx.h"
#include "Window.h"

#include <cassert>

Window::Window(uint32_t width, uint32_t height) {
	glfwInit();
	window = glfwCreateWindow(width, height, "Order independent transparency", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		assert(0);
	}
	glGetError();
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::swapBuffers() {
	glfwSwapBuffers(window);
}

GLFWwindow* Window::getWindow() {
	return window;
}

bool Window::isRunning() {
	return !glfwWindowShouldClose(window);
}
