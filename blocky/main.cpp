#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

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

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.4f, 0.8f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}