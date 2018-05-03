/*
OpenGL 4.3 Practice
by Zintaho (Jin-Seok, Yu)

from 2018-04
 now 2018-05

[TODO : MAIN]
�� �� ���� <= ���ؽ� ����� ���̴����� ó���ؾ���

[TODO : SUB]
�� �ε� �ӵ�

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

	GameObject go("DUNNO", {0.0f,0.0f,0.0f }, { 0,0,0 }, { INIT_SCALE,INIT_SCALE,INIT_SCALE });
	ModelManager::ProcessObject(go);
	Camera mainCam(120, WINDOW_HEIGHT / WINDOW_WIDTH, -1, 1, { go.centerPos.x, go.centerPos.y + 0.5f, go.centerPos.z + 2.0f }, go.centerPos);

	ShaderManager::LoadShader(FILENAME_VSHADER, FILENAME_FSHADER);
	float counter = 0.0f;
	while (not sdlWindow.CheckWindowClosed())
	{
		sdlWindow.Update();
		sdlWindow.Clear();
		go.GetTransform().SetScale({ INIT_SCALE + sinf(counter),INIT_SCALE + cosf(counter),INIT_SCALE});
		ShaderManager::UpdateShader(&go, &mainCam);

		go.GetMesh().DrawMesh();

		sdlWindow.SwapBuffer();

		counter += 0.1f;
	}
	ShaderManager::UnloadShader();
	return 0;
}
