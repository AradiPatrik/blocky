#include "shader.h"
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sstream>

std::string readShader(const std::string & fileName) {
	std::ifstream inFile;
	inFile.open(fileName);
	std::stringstream strStream;
	strStream << inFile.rdbuf();
	std::string str = strStream.str();
	return str;
}

void checkShaderCompilation(GLuint shader) {
	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		fprintf(stderr, "Shader compilation failed\n%s\n", infoLog);
		exit(EXIT_FAILURE);
	}
}

void checkProgramLinkStatus(GLuint program) {
	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(program, 1024, NULL, infoLog);
		fprintf(stderr, "Program linking failed\n%s\n", infoLog);
		exit(EXIT_FAILURE);
	}
}

void validateProgram(GLuint program) {
	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(program, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(program, 1024, NULL, infoLog);
		fprintf(stderr, "Porgram validation failed\n%s\n", infoLog);
		exit(EXIT_FAILURE);
	}
}

Shader::Shader(const std::string & shaderName) {
	
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	this->shaderProgram = glCreateProgram();

	std::string vertexShaderSourceString = readShader(shaderName + "_vs.glsl");
	std::string fragmentShaderSourceString = readShader(shaderName + "_fs.glsl");
	
	const char * vertexShaderCStr = vertexShaderSourceString.c_str();
	const char * fragmentShaderCStr = fragmentShaderSourceString.c_str();

	glShaderSource(this->vertexShader, 1, &vertexShaderCStr, NULL);
	glShaderSource(this->fragmentShader, 1, &fragmentShaderCStr, NULL);
	glCompileShader(this->vertexShader);
	glCompileShader(this->fragmentShader);
	
	checkShaderCompilation(this->vertexShader);
	checkShaderCompilation(this->fragmentShader);

	glAttachShader(this->shaderProgram, this->vertexShader);
	glAttachShader(this->shaderProgram, this->fragmentShader);

	glLinkProgram(this->shaderProgram);
	checkProgramLinkStatus(this->shaderProgram);
	validateProgram(this->shaderProgram);

}

void Shader::bind() {
	glUseProgram(this->shaderProgram);
}

Shader::~Shader() {
	glDeleteShader(this->vertexShader);
	glDeleteShader(this->fragmentShader);
	glDeleteProgram(this->shaderProgram);
}