#pragma once
#include <string>
#include <map>
#include <../GL/glew.h>

enum class ATTRIB_TYPE : GLuint
{
	POS=0,
	UV,
	NORMAL,

	NUM_ATTRIB
};

enum class UNIFORM_TYPE : GLuint
{
	TRANSFORM = 0,
	VIEWPROJ,
	EYE,

	NUM_UNIFORM
};

constexpr GLuint CONVERT(ATTRIB_TYPE t)
{
	return static_cast<GLuint>(t);
}
constexpr GLuint CONVERT(UNIFORM_TYPE t)
{
	return static_cast<GLuint>(t);
}
class Shader
{
public:
	Shader(const char* vsFilename, const char* fsFilename) :
		vsFileName(vsFilename), fsFileName(fsFilename)
	{	
		vsShader = fsShader = shaderProgram = -1;
		InitMap();
	};
	virtual ~Shader();

	inline GLuint* GetAttribs() { return attribs; }
	inline GLuint* GetUniforms() { return uniforms; }
	inline GLuint& GetVS() { return vsShader; }
	inline GLuint& GetFS() { return fsShader; }
	inline GLuint& GetProgram() { return shaderProgram; }
	inline std::string& GetVSSource() { return vsSource; }
	inline std::string& GetFSSource() { return fsSource; }
	inline std::string& GetVSFileName() { return vsFileName; }
	inline std::string& GetFSFileName() { return fsFileName; }

	static std::map<ATTRIB_TYPE, const char*> mapAtr;
	static std::map<UNIFORM_TYPE, const char*> mapUni;
private:
	static void InitMap();

	GLuint attribs[CONVERT(ATTRIB_TYPE::NUM_ATTRIB)];
	GLuint uniforms[CONVERT(UNIFORM_TYPE::NUM_UNIFORM)];
	std::string vsFileName, fsFileName;
	std::string vsSource, fsSource;
	GLuint vsShader, fsShader, shaderProgram;
};
