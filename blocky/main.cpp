#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "shader.h"
#include "mesh.h"
#include "window.h"

int main(int argc, char **argv) {

	Window window(800, 800, "Hello Window");

	std::vector<GLfloat> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};

	std::vector<GLuint> indices = {
		0, 1, 2,
		1, 2, 3
	};
	
	Shader shader("basic_shader");
	Mesh mesh(vertices, indices);
	while (!window.isClosed()) {
		window.clear(0.4f, 0.8f, 0.2f, 1.0f);
		shader.bind();
		mesh.draw();
		window.update();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
