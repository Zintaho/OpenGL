#pragma once
#include <string>
#include <fstream>
#include <vector>

class ShaderManager
{
public:
	static void LoadShader(const char* vertexShaderFileName, const char* fragmentShaderFileName);
	static void UnloadShader();
private:
	static void CheckShaderCompileError(const unsigned int shader, std::string tag);
	static void CheckProgramLinkError(const unsigned int program, std::string tag);

	static std::string vShaderSrc;
	static std::string fShaderSrc;
	static unsigned int vShader, fShader, shaderProgram;
};

