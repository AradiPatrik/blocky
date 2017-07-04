#pragma once

#include <string>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window(GLsizei width, GLsizei height, const std::string& title);
	void update();
	void clear(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
	bool isClosed();
	~Window();
private:
	GLFWwindow *window;
};

void windowResizeCallback(GLFWwindow *window, GLsizei x, GLsizei y);