#pragma once
#include <string>

class ShaderManager
{
public:
	static std::string vertexShaderSource;
	static std::string fragmentShaderSource;

	static void LoadShaderSource(const std::string vertexShaderFileName, const std::string fragmentShaderFileName);
};

