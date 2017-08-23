#pragma once
#include <GLEW\glew.h>
#include <string>
#include <fstream>

class GLSLRunner

{
public:
	GLSLRunner();
	~GLSLRunner();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void linkShaders();

	void addAttribute(const std::string& attributeName);

	GLuint getUniform(const std::string& uniformName);

	void use();
	void unuse();

private:
	void compileShader(const std::string& filePath, GLuint shaderID);

	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	int _numAttributes;
};