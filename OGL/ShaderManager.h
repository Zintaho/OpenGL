#pragma once
#include <string>
#include <fstream>
#include <vector>

class ShaderManager
{
public:
	static std::string vertexShaderSource;
	static std::string fragmentShaderSource;

	static void LoadShaderSource(const std::string vertexShaderFileName, const std::string fragmentShaderFileName);
};

