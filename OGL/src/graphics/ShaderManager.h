#pragma once
#include "Shader.h"
#include <string>

class ShaderManager
{
public:
	void LoadShader(Shader *shader);
	void CompileShader(Shader *shader);
	void LinkProgram(Shader *shader); 
	void UnloadShader(Shader *shader);
private:
	std::string ReadSource(std::string sourcePath);

	void CheckShaderCompileError(const unsigned int shader, std::string tag);
	void CheckProgramLinkError(const unsigned int program, std::string tag);
	void CheckProgramValidateError(const unsigned int program, std::string tag);
};

