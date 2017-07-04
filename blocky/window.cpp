#include "window.h"
#include <iostream>

void windowResizeCallback(GLFWwindow *window, GLsizei x, GLsizei y) {
	glViewport(0, 0, x, y);
}

Window::Window(GLsizei width, GLsizei height, const std::string & title) {
	if (!glfwInit()) {
		std::cerr << "Could not initialize glfw" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!this->window) {
		std::cerr << "Could not create window" << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSetWindowSizeCallback(this->window, windowResizeCallback);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Could not initialize glew" << std::endl;
		exit(EXIT_FAILURE);
	}

	glViewport(0, 0, width, height);
}

void Window::update() {
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

void Window::clear(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Window::isClosed() {
	return glfwWindowShouldClose(this->window);
}

Window::~Window() {
	glfwTerminate();
}