#pragma once
#include <string>

#include "GameObject.h"
#include "Camera.h"

class ShaderManager
{
public:
	static void LoadShader(const char* vertexShaderFileName, const char* fragmentShaderFileName);
	static void UpdateShader(GameObject* ro, Camera* rc);
	static void UnloadShader();

	static GameObject* renderObject;
	static Camera* renderCam;
private:
	enum class UNIFORM_TYPE : unsigned int
	{
		TRANSFORM = 0,
		VIEWPROJ,

		NUM_UNIFORM
	};

	static void CheckShaderCompileError(const unsigned int shader, std::string tag);
	static void CheckProgramLinkError(const unsigned int program, std::string tag);
	static void CheckProgramValidateError(const unsigned int program, std::string tag);

	static std::string vShaderSrc;
	static std::string fShaderSrc;
	static unsigned int vShader, fShader, shaderProgram;
	static int uniforms[static_cast<GLuint>(UNIFORM_TYPE::NUM_UNIFORM)];
};

