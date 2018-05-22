#pragma once
#include "../../src/math/MyMath.h"

#include <GL/glew.h>

class Camera
{
public:
	Camera(float fovy, float aspect, float n, float f, MyMath::Vector3 eye, MyMath::Vector3 at, MyMath::Vector3 up = { 0.0f,1.0f,0.0f }) :
		fovy(fovy), aspect(aspect), n(n), f(f), EYE(eye), AT(at), UP(up)
	{};
	virtual ~Camera();

	inline MyMath::Matrix4x4 MakeMatrix()
	{
		MyMath::Matrix4x4 projMat;
		projMat.SetProjMatrix(fovy, aspect, n, f);
		MyMath::Matrix4x4 viewMat;
		viewMat.SetViewMatrix(EYE, AT, UP);

		MyMath::Matrix4x4 debugMat;
		debugMat.SetIdentityMatrix();
		MyMath::Matrix4x4 returnMat = projMat * viewMat;

		return returnMat;
	}

	inline float& GetFovy() { return fovy; }
	inline float& GetAspect() { return aspect; }
	inline float& GetNear() { return n; }
	inline float& GetFar() { return f; }
	inline MyMath::Vector3& GetEYE() { return EYE; }
	inline MyMath::Vector3& GetAT() { return AT; }
	inline MyMath::Vector3& GetUP() { return UP; }

	inline void SetFovy(const float fovy) { this->fovy = fovy; }
	inline void SetAspect(const float aspect) { this->aspect = aspect; };
	inline void SetNear(const float n) { this->n = n; }
	inline void SetFar(const float f) { this->f = f; }
	inline void SetEYE(const MyMath::Vector3 EYE) { this->EYE = EYE; }
	inline void SetAT(const MyMath::Vector3 AT) { this->AT = AT; }
	inline void SetUP(const MyMath::Vector3 UP) { this->UP = UP; }
private:
	float fovy;
	float aspect;
	float n, f;
	MyMath::Vector3 EYE;
	MyMath::Vector3 AT;
	MyMath::Vector3 UP;
};

