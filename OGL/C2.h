#pragma once
#define ROTX 0
#define ROTY 1
#define ROTZ 2

void _loadShaderSource();
void _checkShaderCompileError(const unsigned int shader, std::string tag);
void _checkProgramLinkError(const unsigned int program, std::string tag);

void _linearScale(float *pos, float x, float y, float z);
void _translate(float *pos, float x, float y, float z);
void _EulerRotate(float *pos, int rot, float amount);
void _homoTransform(float *pos, float sx, float sy, float sz, float tx, float ty, float tz);
void _setVIEW(float mat[4][4], const float *EYE, const float *AT, const float *UP);
void _PROJ(float *pos, float fovy, const float aspect, const float f, const float n);
void _multiply(const float mat[4][4], float *pos);