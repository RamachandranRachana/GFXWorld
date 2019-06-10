#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Shader.h"

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath)
{
	// Create the shaders
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);

	if (vertexShaderStream.is_open())
	{
		std::string line = "";

		while (getline(vertexShaderStream, line))
			vertexShaderCode += "\n" + line;

		vertexShaderStream.close();
	}
	else
	{
		std::cerr << "Impossible to open " << vertexFilePath << ". Check to make sure the file exists and you passed in the right filepath!\n";
		std::cout << "The current working directory is: ";

		// Please for the love of whatever deity/ies you believe in never do something like the next line of code,
		// Especially on non-Windows systems where you can have the system happily execute "rm -rf ~"
		int ret = 0;
#ifdef _WIN32
		ret = system("CD");
#else
		ret = system("pwd");
#endif

		return ret;
	}

	// Read the Fragment Shader code from the file
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);

	if (fragmentShaderStream.is_open())
	{
		std::string line = "";

		while (getline(fragmentShaderStream, line))
			fragmentShaderCode += "\n" + line;

		fragmentShaderStream.close();
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile Vertex Shader
	std::cout << "Vertex Shader:   " << vertexFilePath << std::endl;
	char const* vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderId, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderId);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<char> vertexShaderErrorMessage(static_cast<size_t>(infoLogLength) + 1);
		glGetShaderInfoLog(vertexShaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		std::cerr << &vertexShaderErrorMessage[0] << std::endl;
	}

	// Compile Fragment Shader
	std::cout << "Fragment shader: " << fragmentFilePath;
	char const* fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderId);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(static_cast<size_t>(infoLogLength) + 1);
		glGetShaderInfoLog(fragmentShaderId, infoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cerr << &FragmentShaderErrorMessage[0] << std::endl;
	}

	// Link the program
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	// Check the program
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		std::vector<char> programErrorMessage(static_cast<size_t>(infoLogLength) + 1);
		glGetProgramInfoLog(programId, infoLogLength, NULL, &programErrorMessage[0]);
		std::cerr << &programErrorMessage[0] << std::endl;
	}
	std::cout << std::endl << std::endl;

	glDetachShader(programId, vertexShaderId);
	glDetachShader(programId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}
