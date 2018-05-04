/*
OpenGL 4.3 Practice
by Zintaho (Jin-Seok, Yu)

from 2018-04
 now 2018-05

[TODO : MAIN]
텍스쳐

[TODO : SUB]
모델 로딩 속도

[TODO : MISC]
*/

//Header
#include "MainConstants.h"
#include "SDLWindow.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Camera.h"
#include "GameObject.h"

#include <iostream>

MyMath::Vector3 BezierCameraTest(float f, const MyMath::Vector3 p0, const MyMath::Vector3 p1, const MyMath::Vector3 p2, const MyMath::Vector3 p3)
{
	float d, t;
	t = modff(f, &d);

	MyMath::Vector3 returnVec = p0 * (1 - t)*(1 - t)*(1 - t) + p1 * 3 * (1 - t)*(1 - t)*t + p2 * 3 * (1 - t) * t*t + p3 * t *t *t;

	return returnVec;
}

int SDL_main(int argc, char **argv)
{
	using namespace MyMath;

	SDLWindow sdlWindow(WINDOW_POSX, WINDOW_POSY, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);

	GameObject go("Pikachu", { 0.0f,0.0f,0.0f }, { PI / 18,0,0 }, { INIT_SCALE,INIT_SCALE,INIT_SCALE });
	ModelManager::ProcessObject(go);

	Vector3 p0 = { go.centerPos.x - 2.0f, go.centerPos.y + 3.0f, go.centerPos.z + 5.5f };
	Vector3 p1 = { go.centerPos.x - 0.5f, go.centerPos.y + 2.0f, go.centerPos.z + 2.5f };
	Vector3 p2 = { go.centerPos.x + 1.0f, go.centerPos.y + 1.0f, go.centerPos.z + 4.5f };
	Vector3 p3 = { go.centerPos.x + 6.0f, go.centerPos.y + 2.0f, go.centerPos.z + 10.5f };

	Camera mainCam(90, WINDOW_HEIGHT / WINDOW_WIDTH, -4, 1, p0, go.centerPos);

	ShaderManager::LoadShader(VS_PHONG, FS_PHONG);
	float counter = 0.0f;
	float rotCounter = 0.0f;
	while (not sdlWindow.CheckWindowClosed())
	{
		sdlWindow.Update();
		sdlWindow.Clear();
		//go.GetTransform().SetScale({ INIT_SCALE + (1.0f + sinf(counter)) / 10.0f,INIT_SCALE + (1.0f + cosf(counter)) / 10.0f,INIT_SCALE });
		Vector3 rotVec = go.GetTransform().GetRotate();
		//go.GetTransform().SetRotate({rotVec.x, rotCounter, rotVec.z});
		mainCam.SetEYE(BezierCameraTest(counter, p0, p1, p2, p3));

		Vector3 eye = mainCam.GetEYE();
		std::cout << '(' << eye.x << ',' << eye.y << ',' << eye.z << ')' << std::endl;

		ShaderManager::UpdateShader(&go, &mainCam);

		go.GetMesh().DrawMesh();

		sdlWindow.SwapBuffer();

		counter += 0.004f;
		rotCounter += PI / 180;
	}
	ShaderManager::UnloadShader();
	return 0;
}
