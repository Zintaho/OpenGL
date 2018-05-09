/*
OpenGL 4.3 Practice
by Zintaho (Jin-Seok, Yu)

from 2018-04
 now 2018-05

[TODO : MAIN]
텍스쳐
테셀레이션

[TODO : SUB]
모델 로딩 속도
글로벌 일루미네이션

[TODO : MISC]
*/

//Header
#include "MainConstants.h"
#include "SDLWindow.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Camera.h"
#include "GameObject.h"

int SDL_main(int argc, char **argv)
{
	using namespace MyMath;

	SDLWindow sdlWindow(WINDOW_POSX, WINDOW_POSY, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);

	GameObject go(DEFAULT_MODEL, { 0.0f,0.0f,0.0f }, { PI/12, 0,PI }, { INIT_SCALE,INIT_SCALE,INIT_SCALE });
	ModelManager::ProcessObject(go);

	Vector3 p0 = { go.centerPos.x + 0.0f, go.centerPos.y + 0.0f, go.centerPos.z + 2.5f };

	Camera mainCam(120, WINDOW_HEIGHT / WINDOW_WIDTH, -4, 1, p0, go.centerPos);

	ShaderManager::LoadShader(VS_PHONG, FS_PHONG);
	float counter = 0.0f;
	float rotCounter = 0.0f;
	while (not sdlWindow.CheckWindowClosed())
	{
		sdlWindow.Update();
		sdlWindow.Clear();

		Vector3 rotVec = go.GetTransform().GetRotate();
		go.GetTransform().SetRotate({rotVec.x, rotCounter, rotVec.z});

		ShaderManager::UpdateShader(&go, &mainCam);

		go.GetMesh().DrawMesh();

		sdlWindow.SwapBuffer();

		counter += 0.002f;
		rotCounter += PI / 180;
	}
	ShaderManager::UnloadShader();
	return 0;
}
