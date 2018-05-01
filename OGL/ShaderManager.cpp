#include "ShaderManager.h"

#include <GL/glew.h>
#include <iostream>

std::string ShaderManager::vShaderSrc;
std::string ShaderManager::fShaderSrc;

unsigned int ShaderManager::vShader, ShaderManager::fShader, ShaderManager::shaderProgram;

void ShaderManager::LoadShader(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	const std::string shaderPathHeader = ".\\shader\\";

	std::string path, buffer;
	std::ifstream sourceStream;

	///Load Vertex Shader
	vShaderSrc = "";

	path = (shaderPathHeader + vertexShaderFileName);
	sourceStream.open(path);
	while (not sourceStream.eof())
	{
		getline(sourceStream, buffer);
		vShaderSrc += (buffer + '\n');
	}
	sourceStream.close();

	vShader = glCreateShader(GL_VERTEX_SHADER);
	const char* srcPtr = vShaderSrc.c_str();
	glShaderSource(vShader, 1, &srcPtr, NULL);
	glCompileShader(vShader); 
	CheckShaderCompileError(vShader, "Vertex");

	///Load Fragment Shader
	fShaderSrc = "";

	path = (shaderPathHeader + fragmentShaderFileName);
	sourceStream.open(path);
	while (not sourceStream.eof())
	{
		getline(sourceStream, buffer);
		fShaderSrc += (buffer + '\n');
	}
	sourceStream.close();

	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	srcPtr = fShaderSrc.c_str();
	glShaderSource(fShader, 1, &srcPtr, NULL);
	glCompileShader(fShader);
	CheckShaderCompileError(fShader, "Fragment");

	///Link Program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);
	CheckProgramLinkError(shaderProgram, "Shader Program");
}

void ShaderManager::UnloadShader()
{
	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void ShaderManager::CheckShaderCompileError(const unsigned int shader, std::string tag)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << tag << ":: SHADER COMPILE ERROR\n" << infoLog << std::endl;
	}
}

void ShaderManager::CheckProgramLinkError(const unsigned int program, std::string tag)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << tag << ":: PROGRAM LINK ERROR\n" << infoLog << std::endl;
	}
}
