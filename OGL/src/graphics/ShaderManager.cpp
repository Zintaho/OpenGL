#include "ShaderManager.h"

#include <../GL/glew.h>
#include <iostream>
#include <fstream>

#define ERR_BUFSIZ 1024

void ShaderManager::CompileShader(Shader * shader)
{
	GLuint shaderToCompile = shader->GetVS();
	const char* srcPtr = shader->GetVSSource().c_str();	
	glShaderSource(shaderToCompile, 1, &srcPtr, NULL);
	glCompileShader(shaderToCompile);
	CheckShaderCompileError(shaderToCompile, "Vertex");

	shaderToCompile = shader->GetFS();
	srcPtr = shader->GetFSSource().c_str();
	glShaderSource(shaderToCompile, 1, &srcPtr, NULL);
	glCompileShader(shaderToCompile);
	CheckShaderCompileError(shaderToCompile, "Fragment");
}

void ShaderManager::LinkProgram(Shader * shader)
{
	GLuint vShader = shader->GetVS();
	GLuint fShader = shader->GetFS();
	GLuint shaderProgram = shader->GetProgram();
	GLuint *attribs = shader->GetAttribs();
	GLuint *uniforms = shader->GetUniforms();

	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);

	glLinkProgram(shaderProgram);
	CheckProgramLinkError(shaderProgram, "Shader Program");

	glValidateProgram(shaderProgram);
	CheckProgramValidateError(shaderProgram, "Shader Validate");

	glBindAttribLocation(shaderProgram, CONVERT(ATTRIB_TYPE::POS), Shader::mapAtr[ATTRIB_TYPE::POS]);
	glBindAttribLocation(shaderProgram, CONVERT(ATTRIB_TYPE::UV), Shader::mapAtr[ATTRIB_TYPE::UV]);
	glBindAttribLocation(shaderProgram, CONVERT(ATTRIB_TYPE::NORMAL), Shader::mapAtr[ATTRIB_TYPE::NORMAL]);

	attribs[CONVERT(ATTRIB_TYPE::POS)] = glGetAttribLocation(shaderProgram, Shader::mapAtr[ATTRIB_TYPE::POS]);
	attribs[CONVERT(ATTRIB_TYPE::UV)] = glGetAttribLocation(shaderProgram, Shader::mapAtr[ATTRIB_TYPE::UV]);
	attribs[CONVERT(ATTRIB_TYPE::NORMAL)] = glGetAttribLocation(shaderProgram, Shader::mapAtr[ATTRIB_TYPE::NORMAL]);

	uniforms[CONVERT(UNIFORM_TYPE::TRANSFORM)] = glGetUniformLocation(shaderProgram, Shader::mapUni[UNIFORM_TYPE::TRANSFORM]);
	uniforms[CONVERT(UNIFORM_TYPE::VIEWPROJ)] = glGetUniformLocation(shaderProgram, Shader::mapUni[UNIFORM_TYPE::VIEWPROJ]);
	uniforms[CONVERT(UNIFORM_TYPE::EYE)] = glGetUniformLocation(shaderProgram, Shader::mapUni[UNIFORM_TYPE::EYE]);
}

void ShaderManager::CheckShaderCompileError(const unsigned int shader, std::string tag)
{
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[ERR_BUFSIZ];
		glGetShaderInfoLog(shader, ERR_BUFSIZ, NULL, infoLog);
		std::cerr << tag << ":: SHADER COMPILE ERROR\n" << infoLog << std::endl;
	}
}

void ShaderManager::CheckProgramLinkError(const unsigned int program, std::string tag)
{
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[ERR_BUFSIZ];
		glGetProgramInfoLog(program, ERR_BUFSIZ, NULL, infoLog);
		std::cerr << tag << ":: PROGRAM LINK ERROR\n" << infoLog << std::endl;
	}
}

void ShaderManager::CheckProgramValidateError(const unsigned int program, std::string tag)
{
	GLint success;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[ERR_BUFSIZ];
		glGetProgramInfoLog(program, ERR_BUFSIZ, NULL, infoLog);
		std::cerr << tag << ":: PROGRAM ERROR\n" << infoLog << std::endl;
	}
}

void ShaderManager::UnloadShader(Shader *shader)
{
	GLuint vShader = shader->GetVS();
	GLuint fShader = shader->GetFS();
	GLuint shaderProgram = shader->GetProgram();

	glDetachShader(shaderProgram, vShader);
	glDetachShader(shaderProgram, fShader);
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	glDeleteProgram(shaderProgram);
}

#if 0
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
#endif
