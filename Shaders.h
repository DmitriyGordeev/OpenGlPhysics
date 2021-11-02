#pragma once
#include <string>
#include <GL/glew.h>

class Shaders
{
public:
	Shaders();
	~Shaders();

	void compile(const std::string& vertexShader, const std::string& pixelShader);
	void link() const;
	void addAttribute(const std::string& attributeName);

	GLuint getUniformLocation(const std::string& uniformName) const;

	void use() const;
	void unuse() const;

private:
	int _numAttributes;
	GLuint _shaderProgramID;
	GLuint _vertexShaderID;
	GLuint _pixelShaderID;

	static void _compileSingleShader(const std::string& shaderFilename, GLuint id);
};

