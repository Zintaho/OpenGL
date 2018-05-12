#include "ShaderManager.h"
#include "MyMath.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <vector>

GameObject* ShaderManager::renderObject;
Camera* ShaderManager::renderCam;

std::string ShaderManager::vShaderSrc;
std::string ShaderManager::fShaderSrc;
int ShaderManager::uniforms[static_cast<unsigned int>(UNIFORM_TYPE::NUM_UNIFORM)];
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

	glBindAttribLocation(shaderProgram, 0, "position");
	glBindAttribLocation(shaderProgram, 1, "normal");

	glLinkProgram(shaderProgram);
	CheckProgramLinkError(shaderProgram, "Shader Program");

	glValidateProgram(shaderProgram);
	CheckProgramValidateError(shaderProgram, "Shader Validate");

	uniforms[static_cast<unsigned int>(UNIFORM_TYPE::TRANSFORM)] = glGetUniformLocation(shaderProgram, "transform");
	uniforms[static_cast<unsigned int>(UNIFORM_TYPE::VIEWPROJ)] = glGetUniformLocation(shaderProgram, "vp");
	uniforms[static_cast<unsigned int>(UNIFORM_TYPE::EYE)] = glGetUniformLocation(shaderProgram, "eye");
}

void ShaderManager::UpdateShader(GameObject * ro, Camera * rc)
{
	glUseProgram(shaderProgram);

	renderObject = ro;
	renderCam = rc;

	MyMath::Matrix4x4 transMat = ro->GetTransform().MakeMatrix();
	MyMath::Matrix4x4 VPMat = rc->MakeMatrix();

	glUniformMatrix4fv(uniforms[static_cast<unsigned int>(UNIFORM_TYPE::TRANSFORM)], 1, GL_FALSE, transMat.GetMatrix());
	glUniformMatrix4fv(uniforms[static_cast<unsigned int>(UNIFORM_TYPE::VIEWPROJ)], 1, GL_FALSE, VPMat.GetMatrix());
	MyMath::Vector3 eye = renderCam->GetEYE();
	GLfloat fEye[3] = { eye.x,eye.y,eye.z };
	glUniform3fv(uniforms[static_cast<unsigned int>(UNIFORM_TYPE::VIEWPROJ)], 1, fEye);
}

void ShaderManager::UnloadShader()
{
	glDetachShader(shaderProgram, vShader);
	glDetachShader(shaderProgram, fShader);
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	glDeleteProgram(shaderProgram);
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

void ShaderManager::CheckProgramValidateError(const unsigned int program, std::string tag)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << tag << ":: PROGRAM ERROR\n" << infoLog << std::endl;
	}
}