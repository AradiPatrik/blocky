#include "shader.h"
#include <cstdlib>
#include <cstdio>

/*
	reads the given file contents, and returns a null terminated string
	REMEMBER TO CALL FREE AFTER USING THE RETURNED STRING
*/
char * readFile(const char * fileName) {
	char *string;
	size_t fileSize;
	size_t result;
	FILE *filePointer;

	filePointer = fopen(fileName, "rb");
	fseek(filePointer, 0, SEEK_END);
	fileSize = ftell(filePointer);
	rewind(filePointer);

	string = (char*) malloc(fileSize * sizeof(char));
	if (string == NULL) {
		fputs("Out of memory\n", stderr);
		exit(EXIT_FAILURE);
	}

	result = fread(string, sizeof(char), fileSize, filePointer);
	if (result != fileSize) {
		fputs("Read error\n", stderr);
		exit(EXIT_FAILURE);
	}

	string[fileSize] = '\0';
	fclose(filePointer);
	return string;
}

/*
	creates and compiles shader, returns the compiled shader
*/
GLuint createShader(const char * fileName, GLenum shaderType) {
	GLuint shader;
	char *shaderSourceString = readFile(fileName);
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSourceString, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		fprintf(stderr, "Shader compilation failed\n%s\n", infoLog);
		exit(EXIT_FAILURE);
	}

	free(shaderSourceString);
	return shader;
}

/*
	creates program, and attaches the shaders to it, returns the linked and verified program
*/
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	GLint success;
	GLchar infoLog[1024];
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
		fprintf(stderr, "Program is not valid\n%s\n", infoLog);
		exit(EXIT_FAILURE);
	}

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
		fprintf(stderr, "Program linking failed\n%s\n", infoLog);
		exit(EXIT_FAILURE);
	}

	return shaderProgram;
}