#include "Shader.h"
#include <fstream>
std::map<ATTRIB_TYPE, const char*> Shader::mapAtr;
std::map<UNIFORM_TYPE, const char*> Shader::mapUni;

void Shader::InitMap()
{
	mapAtr[ATTRIB_TYPE::POS] = "position";
	mapAtr[ATTRIB_TYPE::UV] = "uv";
	mapAtr[ATTRIB_TYPE::NORMAL] = "normal";

	mapUni[UNIFORM_TYPE::TRANSFORM] = "transform";
	mapUni[UNIFORM_TYPE::VIEW] = "view";
	mapUni[UNIFORM_TYPE::PROJ] = "proj";
	mapUni[UNIFORM_TYPE::EYE] = "eye";
}

std::string Shader::ReadSource(std::string sourcePath)
{
	const std::string shaderPathHeader = ".\\shader\\";
	const std::string shaderPathFooter = ".glsl";

	std::string path, buffer;
	std::ifstream sourceStream;

	std::string returnSource = "";

	path = (shaderPathHeader + sourcePath + shaderPathFooter);
	sourceStream.open(path);

	if (sourceStream.is_open())
	{
		while (not sourceStream.eof())
		{
			getline(sourceStream, buffer);
			returnSource += (buffer + '\n');
		}
		sourceStream.close();
	}

	return returnSource;
}

Shader::~Shader()
{
	glDetachShader(shaderProgram, vsShader);
	if (bTessOn)
	{
		glDetachShader(shaderProgram, tcsShader);
		glDetachShader(shaderProgram, tesShader);
	}
	if (bGSOn)
	{
		glDetachObjectARB(shaderProgram, gsShader);
	}
	glDetachShader(shaderProgram, fsShader);
	glDeleteProgram(shaderProgram);
}