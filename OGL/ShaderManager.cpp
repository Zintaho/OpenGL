#include "ShaderManager.h"

#include <fstream>
#include <string>
#include <vector>

std::string ShaderManager::vertexShaderSource;
std::string ShaderManager::fragmentShaderSource;

void ShaderManager::LoadShaderSource(const std::string vertexShaderFileName, const std::string fragmentShaderFileName)
{
	using namespace std;

	const std::string shaderPathHeader = ".\\shader\\";

	string path, buffer;
	ifstream sourceStream;
	///Load Vertex Shader
	if (vertexShaderFileName.size() != 0)
	{
		vertexShaderSource = "";

		path = (shaderPathHeader + vertexShaderFileName);
		sourceStream.open(path);
		while (not sourceStream.eof())
		{
			getline(sourceStream, buffer);
			vertexShaderSource += (buffer + '\n');
		}
		sourceStream.close();
	}
	///Load Fragment Shader
	if (fragmentShaderFileName.size() != 0)
	{
		fragmentShaderSource = "";

		path = (shaderPathHeader + fragmentShaderFileName);
		sourceStream.open(path);
		while (not sourceStream.eof())
		{
			getline(sourceStream, buffer);
			fragmentShaderSource += (buffer + '\n');
		}
		sourceStream.close();
	}
}