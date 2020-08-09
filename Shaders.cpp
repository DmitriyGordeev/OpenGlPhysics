#include "Shaders.h"
#include "errors.h"

#include <vector>
#include <fstream>

Shaders::Shaders() : _numAttributes(0), _shaderProgramID(0), _vertexShaderID(0), _pixelShaderID(0)
{
}

Shaders::~Shaders()
{
}

void Shaders::compile(const std::string& vertexShader, const std::string& pixelShader)
{
	//Combine two or more shaders in one object
	//Get an empty shader program object
	_shaderProgramID = glCreateProgram();

	//Creating shaders
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
		fatal("Error: Vertex Shader failed to be created!");

	_pixelShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_pixelShaderID == 0)
		fatal("Error: Pixel Shader failed to be created!");

	//Compiling shaders
	_compileSingleShader(vertexShader, _vertexShaderID);
	_compileSingleShader(pixelShader, _pixelShaderID);
}

void Shaders::link()
{
	//Attaching shaders to program
	glAttachShader(_shaderProgramID, _vertexShaderID);
	glAttachShader(_shaderProgramID, _pixelShaderID);

	//Linking program
	glLinkProgram(_shaderProgramID);

	//Error of linking handling
	GLint isLinked = 0;
	glGetProgramiv(_shaderProgramID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_shaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(_shaderProgramID, maxLength, &maxLength, &infoLog[0]);

		//Don't need the program anymore
		glDeleteProgram(_shaderProgramID);

		//Deleting shaders
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_pixelShaderID);

		//Print logged error message
		std::printf("%s\n", &(infoLog[0]));
		fatal("Shaders failed to link");

		return;
	}

	//Detaching shader after a successful link!
	glDetachShader(_shaderProgramID, _vertexShaderID);
	glDetachShader(_shaderProgramID, _pixelShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_pixelShaderID);
}

GLuint Shaders::getUniformLocation(const std::string& uniformName)
{
	GLuint location = glGetUniformLocation(_shaderProgramID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
		fatal("Uniform " + uniformName + "nor found in shader");

	return location;
}

void Shaders::addAttribute(const std::string& attributeName)
{
	glBindAttribLocation(_shaderProgramID, _numAttributes++, attributeName.c_str());
}

void Shaders::use()
{
	//Using shader
	glUseProgram(_shaderProgramID);

	//Enable each bound vertex attribute
	for (int i = 0; i < _numAttributes; i++)
		glEnableVertexAttribArray(i);
}

void Shaders::unuse()
{
	//Stop using program
	glUseProgram(0);

	//Disable each bound vertex attribute
	for (int i = 0; i < _numAttributes; i++)
		glDisableVertexAttribArray(i);
}

void Shaders::_compileSingleShader(const std::string& shaderFilename, GLuint id)
{
	//Reading shader files
	std::ifstream shaderFile(shaderFilename);
	if (shaderFile.fail())
		fatal("Error: Failed to open " + shaderFilename);

	std::string fileContent = "";
	std::string line;
	while (std::getline(shaderFile, line))
		fileContent += line + "\n";

	shaderFile.close();

	//Loading shader to openGL
	const char* contentsPtr = fileContent.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	//Compiling shader
	glCompileShader(id);

	//Error handling
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);
		//Print logged error message
		std::printf("%s\n", &(errorLog[0]));
		fatal("Shader" + shaderFilename + " failed to compile");

		return;
	}
}
