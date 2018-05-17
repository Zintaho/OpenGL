#include "Shader.h"
std::map<ATTRIB_TYPE, const char*> Shader::mapAtr;
std::map<UNIFORM_TYPE, const char*> Shader::mapUni;

void Shader::InitMap()
{
	mapAtr[ATTRIB_TYPE::POS] = "position";
	mapAtr[ATTRIB_TYPE::UV] = "uv";
	mapAtr[ATTRIB_TYPE::NORMAL] = "normal";

	mapUni[UNIFORM_TYPE::TRANSFORM] = "transform";
	mapUni[UNIFORM_TYPE::VIEWPROJ] = "vp";
	mapUni[UNIFORM_TYPE::EYE] = "eye";
}
Shader::~Shader()
{
}