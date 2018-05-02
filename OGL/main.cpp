/*
OpenGL 4.3 Practice
by Zintaho (Jin-Seok, Yu)

from 2018-04
 now 2018-05

[TODO : MAIN]
퐁 모델 적용 <= 버텍스 노멀을 쉐이더에서 처리해야함

[TODO : SUB]

[TODO : MISC]
*/

//Header
#include "MainConstants.h"
#include "SDLWindow.h"
#include "ShaderManager.h"

#include "Mesh.h"

#include "Camera.h"
#include "GameObject.h"
#include "ModelManager.h"
#include "MyMath.h"

int WinMain(int argc, char **argv)
{
	using namespace MyMath;

	SDLWindow sdlWindow(WINDOW_POSX, WINDOW_POSY, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);

	GameObject go("PC", { 0.0f,0.0f,0.0f }, { 0,0,0 }, { 2.0f,2.0f,2.0f });
	ModelManager::ProcessObject(go);
	size_t cnt = ModelManager::vertice.size();

	Camera mainCam(120, WINDOW_HEIGHT / WINDOW_WIDTH, -1, 1, { go.centerPos.x, go.centerPos.y + 0.5f, go.centerPos.z + 2.0f }, go.centerPos);

	for (int i = 0; i < cnt; ++i)
	{
		ModelManager::vertice[i].Pos = mainCam.MakeMatrix() * go.GetTransform().MakeMatrix() * ModelManager::vertice[i].Pos;
	}

	while (not sdlWindow.CheckWindowClosed())
	{
		sdlWindow.Clear();
		ShaderManager::LoadShader(FILENAME_VSHADER, FILENAME_FSHADER);

		go.GetMesh().DrawMesh();

		sdlWindow.Update();
		ShaderManager::UnloadShader();
	}
	return 0;
}
