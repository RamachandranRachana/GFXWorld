#pragma once

#include <string>

#include <GL/glew.h>

class Shader
{
public:
	Shader() = delete;
	explicit Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();
	void Use();

private:
	GLuint pvLoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	GLuint m_shaderID;
	std::string m_vertexShaderPath, m_fragmentShaderPath;
};
