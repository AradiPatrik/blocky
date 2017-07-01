#pragma once

#include <GL\glew.h>

GLuint createShader(const char* fileName, GLenum shaderType);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);