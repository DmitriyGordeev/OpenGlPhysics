#pragma once
#include <string>
#include <GL/glew.h>

class Shaders
{
public:
	Shaders();
	~Shaders();

	void compile(const std::string& vertexShader, const std::string& pixelShader);
	void link();
	void addAttribute(const std::string& attributeName);

	GLuint getUniformLocation(const std::string& uniformName);

	void use();
	void unuse();

private:
	int _numAttributes;
	GLuint _shaderProgramID;
	GLuint _vertexShaderID;
	GLuint _pixelShaderID;

	void _compileSingleShader(const std::string& shaderFilename, GLuint id);
};

