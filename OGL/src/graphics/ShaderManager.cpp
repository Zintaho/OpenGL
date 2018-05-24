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

	if (shader->isTessOn())
	{
		shaderToCompile = shader->GetTCS();
		const char* srcPtr = shader->GetTCSSource().c_str();
		glShaderSource(shaderToCompile, 1, &srcPtr, NULL);
		glCompileShader(shaderToCompile);
		CheckShaderCompileError(shaderToCompile, "TESS Control");

		shaderToCompile = shader->GetTES();
		srcPtr = shader->GetTESSource().c_str();
		glShaderSource(shaderToCompile, 1, &srcPtr, NULL);
		glCompileShader(shaderToCompile);
		CheckShaderCompileError(shaderToCompile, "TESS Evaluation");
	}
}

void ShaderManager::LinkProgram(Shader * shader)
{
	GLuint vShader = shader->GetVS();
	GLuint fShader = shader->GetFS();	
	GLuint tcShader, teShader;
	GLuint shaderProgram = shader->GetProgram();
	GLuint *attribs = shader->GetAttribs();
	GLuint *uniforms = shader->GetUniforms();

	///ATTACH SHADERS
	glAttachShader(shaderProgram, vShader);
	if (shader->isTessOn())
	{
		tcShader = shader->GetTCS();
		teShader = shader->GetTES();
		glAttachShader(shaderProgram, tcShader);
		glAttachShader(shaderProgram, teShader);
	}
	glAttachShader(shaderProgram, fShader);

	glLinkProgram(shaderProgram);
	CheckProgramLinkError(shaderProgram, "Shader Program");
	glValidateProgram(shaderProgram);
	CheckProgramValidateError(shaderProgram, "Shader Validate");

	///DELETE SHADERS (You are able to delete shaders if they are compiled)
	glDeleteShader(vShader);
	if (shader->isTessOn())
	{
		glDeleteShader(tcShader);
		glDeleteShader(teShader);
	}
	glDeleteShader(fShader);

	glBindAttribLocation(shaderProgram, CONVERT(ATTRIB_TYPE::POS), Shader::mapAtr[ATTRIB_TYPE::POS]);
	glBindAttribLocation(shaderProgram, CONVERT(ATTRIB_TYPE::UV), Shader::mapAtr[ATTRIB_TYPE::UV]);
	glBindAttribLocation(shaderProgram, CONVERT(ATTRIB_TYPE::NORMAL), Shader::mapAtr[ATTRIB_TYPE::NORMAL]);

	attribs[CONVERT(ATTRIB_TYPE::POS)] = glGetAttribLocation(shaderProgram, Shader::mapAtr[ATTRIB_TYPE::POS]);
	attribs[CONVERT(ATTRIB_TYPE::UV)] = glGetAttribLocation(shaderProgram, Shader::mapAtr[ATTRIB_TYPE::UV]);
	attribs[CONVERT(ATTRIB_TYPE::NORMAL)] = glGetAttribLocation(shaderProgram, Shader::mapAtr[ATTRIB_TYPE::NORMAL]);

	uniforms[CONVERT(UNIFORM_TYPE::TRANSFORM)] = glGetUniformLocation(shaderProgram, Shader::mapUni[UNIFORM_TYPE::TRANSFORM]);
	uniforms[CONVERT(UNIFORM_TYPE::VIEW)] = glGetUniformLocation(shaderProgram, Shader::mapUni[UNIFORM_TYPE::VIEW]);
	uniforms[CONVERT(UNIFORM_TYPE::PROJ)] = glGetUniformLocation(shaderProgram, Shader::mapUni[UNIFORM_TYPE::PROJ]);
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