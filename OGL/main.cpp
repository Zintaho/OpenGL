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
#include "Display.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Camera.h"
#include "GameObject.h"

int SDL_main(int argc, char **argv)
{
	using namespace MyMath;

	///Set DisplayOption
	DisplayOption displayOption;
	displayOption.FULL_SCREEN = false;
	displayOption.FULL_SCREEN_CUR_RESOLUTION = false;
	displayOption.VISIBLE = true;
	displayOption.RESIZABLE = false;
	displayOption.BORDERLESS = true;
	displayOption.MINIMIZED = false;
	displayOption.MAXIMIZED = false;
	displayOption.INPUT_GRABBED = false;
	displayOption.INPUT_FOCUS = false;
	displayOption.MOUSE_FOCUS = false;
	displayOption.MOUSE_CAPTURE = false;
	displayOption.HIGH_DPI = true;

	displayOption.ADAPTIVE_VSYNC = true;
	///Create Display
	Display display(displayOption);
	display.CreateDisplay();
	///Loop
	while (display.CheckState() != STATE::END)
	{
		display.Clear();
		display.SwapBuffer();
		display.CheckEvent();
	}

	//Mesh *trophyMesh = new Mesh("Trophy");
	//trophyMesh->LoadMeshFile();
	//trophyMesh->InitMesh(&ModelManager::vertice[0], ModelManager::verticeNum, &ModelManager::indice[0], ModelManager::indiceNum);

	//Vector3 centerPos = ModelManager::centerPos;
	//GameObject *go[OBJECT_NUM];
	//for (int i = 0; i < OBJECT_NUM; ++i)
	//{
	//	go[i] = new GameObject(trophyMesh, {0.0f, i * 0.55f, 0.0f }, {0, i * PI/3,PI }, { INIT_SCALE,INIT_SCALE,INIT_SCALE});
	//	go[i]->centerPos = { centerPos.x, centerPos.y + i * 0.5f, centerPos.z };
	//}

	//Vector3 p0 = { go[0]->centerPos.x + 0.0f, go[0]->centerPos.y + 0.5f, go[0]->centerPos.z + 2.5f };

	//Camera mainCam(100, WINDOW_HEIGHT / WINDOW_WIDTH, -1, 1, p0, go[0]->centerPos);

	//ShaderManager::LoadShader(VS_PHONG, FS_PHONG);
	//float counter = 0.0f;
	//float rotCounter = 0.0f;
	//while (not display.CheckWindowClosed())
	//{
	//	display.Update();
	//	display.Clear();
	//	
	//	for (int i = 0; i < OBJECT_NUM; ++i)
	//	{
	//		Vector3 transVec = go[i]->GetTransform().GetTrans();
	//		//go[i]->GetTransform().SetTrans({ transVec.x,transVec.y + 1.0f * i,transVec.z });

	//		ShaderManager::UpdateShader(go[i], &mainCam);
	//		go[i]->GetMesh()->DrawMesh();
	//	}

	//	display.SwapBuffer();
	//}
	//ShaderManager::UnloadShader();

	//for (int i = 0; i < OBJECT_NUM; ++i)
	//{
	//	delete go[i];
	//}
	//delete trophyMesh;



	return 0;
}
