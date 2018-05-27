#pragma once
#include <string>
#include "Shader.h"

class ShaderManager
{
public:
	void ProcessShader(Shader *shader);
private:
	void CompileShader(Shader *shader);
	void LinkProgram(Shader *shader);
	void CheckShaderCompileError(const unsigned int shader, std::string tag);
	void CheckProgramLinkError(const unsigned int program, std::string tag);
	void CheckProgramValidateError(const unsigned int program, std::string tag);
};

