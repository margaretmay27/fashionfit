#include "GLSLRunner.h"
#include <vector>

#include "Error.h"

GLSLRunner::GLSLRunner() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0)
{
}


GLSLRunner::~GLSLRunner()
{
}

void GLSLRunner::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {

	_programID = glCreateProgram();

	_vertexShaderID	= glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("Vertex Shader Failed to Create");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		fatalError("Fragment Shader Failed to Create");
	}

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);

}

	

void GLSLRunner::linkShaders() {

	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	glLinkProgram(_programID);

	//error checking
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, (int*) &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxlength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxlength);
		std::vector<char> infoLog(maxlength);

		glGetProgramInfoLog(_programID, maxlength, &maxlength, &infoLog[0]);

		glDeleteProgram(_programID);

		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		fatalError("Shaders Failed to Link");
	}

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);

	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLRunner::compileShader(const std::string& filePath, GLuint shaderID)
{
	std::ifstream fileStream(filePath);
	if (fileStream.fail()) {
		fatalError("Failed to Open " + filePath);
	}

	std::string data, line;
	while (std::getline(fileStream, line)) {
		data += line + "\n";
	}
	fileStream.close();

	const char* vertexFileContents = data.c_str();
	glShaderSource(shaderID, 1, &vertexFileContents, nullptr);
	glCompileShaderARB(shaderID);
}

void GLSLRunner::addAttribute(const std::string& attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLuint GLSLRunner::getUniform(const std::string & uniformName)
{
	GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform " + uniformName + " not found.");
	}
	return location;
}

void GLSLRunner::use()
{
	glUseProgram(_programID);
	//use attributes
	for (int i = 0; i < _numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLRunner::unuse()
{
	glUseProgram(0);
}
