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
	VIEW,
	PROJ,
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
		InitMap();

		shaderProgram = glCreateProgram();
		vsShader = glCreateShader(GL_VERTEX_SHADER);
		fsShader = glCreateShader(GL_FRAGMENT_SHADER);

		vsSource = ReadSource(vsFileName);
		fsSource = ReadSource(fsFileName);
	};
	Shader(const char* vsFilename, const char* fsFilename, const char* gsFilename) :
		vsFileName(vsFilename), fsFileName(fsFilename), gsFileName(gsFilename)
	{
		InitMap();
		bGSOn = true;

		shaderProgram = glCreateProgram();
		vsShader = glCreateShader(GL_VERTEX_SHADER);
		fsShader = glCreateShader(GL_FRAGMENT_SHADER);
		gsShader = glCreateShader(GL_GEOMETRY_SHADER);

		vsSource = ReadSource(vsFileName);
		fsSource = ReadSource(fsFileName);
		gsSource = ReadSource(gsFileName);
	};
	Shader(const char* vsFilename, const char* fsFilename, const char* gsFilename, const char* tcsFilename, const char* tesFilename) :
		vsFileName(vsFilename), fsFileName(fsFilename), gsFileName(gsFilename), tcsFileName(tcsFilename), tesFileName(tesFilename)
	{
		InitMap();
		//bGSOn = true;
		bTessOn = true;

		shaderProgram = glCreateProgram();
		vsShader = glCreateShader(GL_VERTEX_SHADER);
		fsShader = glCreateShader(GL_FRAGMENT_SHADER);
		gsShader = glCreateShader(GL_GEOMETRY_SHADER);
		tcsShader = glCreateShader(GL_TESS_CONTROL_SHADER);
		tesShader = glCreateShader(GL_TESS_EVALUATION_SHADER);

		vsSource = ReadSource(vsFileName);
		fsSource = ReadSource(fsFileName);
		gsSource = ReadSource(gsFileName);
		tcsSource = ReadSource(tcsFileName);
		tesSource = ReadSource(tesFileName);
	};
	virtual ~Shader();

	inline GLuint* GetAttribs() { return attribs; }
	inline GLuint* GetUniforms() { return uniforms; }
	inline GLuint& GetVS() { return vsShader; }
	inline GLuint& GetFS() { return fsShader; }
	inline GLuint& GetGS() { return gsShader; }
	inline GLuint& GetTCS() { return tcsShader; }
	inline GLuint& GetTES() { return tesShader; }
	inline GLuint& GetProgram() { return shaderProgram; }
	inline std::string& GetVSSource() { return vsSource; }
	inline std::string& GetFSSource() { return fsSource; }
	inline std::string& GetGSSource() { return gsSource; }
	inline std::string& GetTCSSource() { return tcsSource; }
	inline std::string& GetTESSource() { return tesSource; }
	inline std::string& GetVSFileName() { return vsFileName; }
	inline std::string& GetFSFileName() { return fsFileName; }
	inline std::string& GetTCSFileName() { return tcsFileName; }
	inline std::string& GetTESFileName() { return tesFileName; }
	inline bool isGSOn() { return bGSOn; }
	inline bool isTessOn() { return bTessOn; }

	static std::map<ATTRIB_TYPE, const char*> mapAtr;
	static std::map<UNIFORM_TYPE, const char*> mapUni;
private:
	static void InitMap();
	std::string ReadSource(std::string sourcePath);

	GLuint attribs[CONVERT(ATTRIB_TYPE::NUM_ATTRIB)];
	GLuint uniforms[CONVERT(UNIFORM_TYPE::NUM_UNIFORM)];
	///VS, FS
	std::string vsFileName, fsFileName;
	std::string vsSource, fsSource;
	GLuint vsShader, fsShader, shaderProgram;
	///GS
	std::string gsFileName;
	std::string gsSource;
	GLuint gsShader;
	bool bGSOn = false;
	///TESS CS, ES
	std::string tcsFileName, tesFileName;
	std::string tcsSource, tesSource;
	GLuint tcsShader, tesShader;
	bool bTessOn = false;
};
