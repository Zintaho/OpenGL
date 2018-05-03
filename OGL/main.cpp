/*
OpenGL 4.3 Practice
by Zintaho (Jin-Seok, Yu)

from 2018-04
 now 2018-05

[TODO : MAIN]
퐁 모델 적용 <= 버텍스 노멀을 쉐이더에서 처리해야함

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

int SDL_main(int argc, char **argv)
{
	using namespace MyMath;

	SDLWindow sdlWindow(WINDOW_POSX, WINDOW_POSY, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);

	GameObject go("Pikachu", {0.0f,0.0f,0.0f }, {PI/36,0,0 }, { INIT_SCALE,INIT_SCALE,INIT_SCALE });
	ModelManager::ProcessObject(go);
	Camera mainCam(120, WINDOW_HEIGHT / WINDOW_WIDTH, -1, 1, { go.centerPos.x, go.centerPos.y + 0.5f, go.centerPos.z + 2.0f }, go.centerPos);

	ShaderManager::LoadShader(FILENAME_VSHADER, FILENAME_FSHADER);
	float counter = 0.0f;
	float rotCounter = 0.0f;
	while (not sdlWindow.CheckWindowClosed())
	{
		sdlWindow.Update();
		sdlWindow.Clear();
		//go.GetTransform().SetScale({ INIT_SCALE + (1.0f + sinf(counter))/10.0f,INIT_SCALE + (1.0f + cosf(counter))/10.0f,INIT_SCALE});
		Vector3 rotVec = go.GetTransform().GetRotate();
		go.GetTransform().SetRotate({rotVec.x, rotCounter, rotVec.z});
		ShaderManager::UpdateShader(&go, &mainCam);

		go.GetMesh().DrawMesh();

		sdlWindow.SwapBuffer();

		counter += 0.1f;
		rotCounter += PI / 180;
	}
	ShaderManager::UnloadShader();
	return 0;
}
