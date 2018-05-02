/*
OpenGL 4.3 Practice
by Zintaho (Jin-Seok, Yu)

from 2018-04
 now 2018-05

[TODO : MAIN]
카메라 클래스
퐁 모델 적용

드로우 개선 (ArrayBuffer가 한도를 넘어서면 crash - 인텔내장그래픽 문제로 보임)

로컬 -> 월드 매트릭스

[TODO : SUB]
모델 로더 개선(속도가 느림, uv좌표 읽어와야함, 노멀벡터 읽어와야 함)

[TODO : MISC]
헤더 정리
*/

//Header
#include "MainConstants.h"
#include "SDLWindow.h"
#include "ShaderManager.h"

#include "Mesh.h"

#include "GameObject.h"
#include "ModelManager.h"
#include "MyMath.h"

int WinMain(int argc, char **argv)
{
	using namespace MyMath;

	SDLWindow sdlWindow(WINDOW_POSX,WINDOW_POSY,WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);

	GameObject go("Moritaka");
	ModelManager::ProcessObject(go);
	size_t cnt = ModelManager::vertice.size();

			struct Camera2
			{
				Vector3 EYE;
				Vector3 AT;
				Vector3 UP;
				float fovy;
				float aspect;
				float n, f;
			};

			Camera2 mainCam =
			{
			{0.0f,0.0f,2.0f},	//EYE
			{0.0f,0.0f,0.5f},	//AT
			{0.0f,1.0f,0.0f},	//UP
			120,//fovy
			WINDOW_HEIGHT / WINDOW_WIDTH,//aspect
			-1,1//n,f
			};

			mainCam.EYE.x = go.position.x + 0.5f;
			mainCam.EYE.y = go.position.y + 0.5f;
			mainCam.EYE.z = go.position.z + 2.0f;

			mainCam.AT.x = go.position.x;
			mainCam.AT.y = go.position.y;
			mainCam.AT.z = go.position.z;

			Matrix4x4 scaleMat;
			scaleMat.SetScaleMatrix(0.1f, 0.1f, 0.1f);

			Matrix4x4 translateMat;
			translateMat.SetTranslateMatrix(0.0f, 8.0f, 0.0f);
			
			Matrix4x4 viewMat;
			viewMat.SetViewMatrix(mainCam.EYE, mainCam.AT, mainCam.UP);

			Matrix4x4 projMat;
			projMat.SetProjMatrix(mainCam.fovy, mainCam.aspect, mainCam.n, mainCam.f);

			for (int i = 0; i < cnt; ++i)
			{
				ModelManager::vertice[i].Pos = projMat * viewMat * translateMat * scaleMat * ModelManager::vertice[i].Pos;
			}

	Mesh mesh(&ModelManager::vertice[0], cnt);
	
	while (not sdlWindow.CheckWindowClosed())
	{
		sdlWindow.Clear();
		ShaderManager::LoadShader(FILENAME_VSHADER, FILENAME_FSHADER);

		mesh.DrawMesh();

		sdlWindow.Update();
		ShaderManager::UnloadShader();
	}
	return 0;
}
