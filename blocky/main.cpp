#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "shader.h"
#include "mesh.h"

int main(int argc, char **argv) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize glfw!" << std::endl;
		return EXIT_FAILURE;
	}

	GLFWwindow *window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create winodw!" << std::endl;
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize glew" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, 500, 500);

	std::vector<GLfloat> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};

	std::vector<GLuint> indices = {
		0, 1, 2,
		1, 2, 3
	};
	GLuint vertexShader = createShader("basic_shader_vs.glsl", GL_VERTEX_SHADER);
	GLuint fragmentShader = createShader("basic_shader_fs.glsl", GL_FRAGMENT_SHADER);
	GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);
	Mesh mesh(vertices, indices);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.4f, 0.8f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		mesh.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
