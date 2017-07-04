#pragma once

#include <GL\glew.h>
#include <string>

class Shader
{
public:
	Shader(const std::string& fileName);
	void bind();
	~Shader();
private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
};