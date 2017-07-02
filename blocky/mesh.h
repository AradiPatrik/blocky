#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

class Mesh
{
public:
	Mesh(std::vector<GLfloat> &vertices, std::vector<GLuint>& indices);

	void draw() const;

	~Mesh();
private:
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	GLuint VAO, VBO, EBO;
};
