#pragma once
class Camera
{
public:
	float EYE[3];
	float AT[3];
	float UP[3];
	float fovy;
	float aspect;
	float n, f;

	Camera();
	~Camera();
};

