/*
OpenGL 4.3 Practice
by Zintaho (YU Jin-seok)

from 2018-04
 now 2018-05

[TODO : MAIN]
텍스쳐
테셀레이션

[TODO : SUB]
EventHandler
모델 로딩 속도
글로벌 일루미네이션

[TODO : MISC]
*/

//Header
#include "MainConstants.h"
#include "src/core/Display.h"
#include "src/graphics/Renderer.h"
#include "src/graphics/ModelManager.h"
#include "src/graphics/ShaderManager.h"
//#include "ShaderManager.h"
//#include "ModelManager.h"
//#include "Camera.h"
//#include "GameObject.h"

void EventHandle(EventInfo eventInfo, RenderContext *rc);

int main(int argc, char **argv)
{
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
	///Create Display & Renderer
	Display display(displayOption);
	display.CreateDisplay();
	Renderer renderer(&display);
	///Create Manager;
	ModelManager modelManager;
	ShaderManager shaderManager;
	///Create Components
	Mesh mesh("Pikachu");
	Shader shader("vertex", "fragment");

	MyMath::Vector3 pos(0, 0, 0.0f);
	MyMath::Vector3 rot(0, 0, 0);
	MyMath::Vector3 scale(0.5f, 0.5f, 0.5f);
	Transform transform(pos, rot, scale);

	GameObject gameObject(&mesh, transform);

	float fovy = (1.0f / 2.0f) * MyMath::PI;
	float aspect = display.GetAspect();
	float n = 1;
	float f = 1000;
	MyMath::Vector3 eye(0.0f, 0.0f, 3.0f);
	MyMath::Vector3 at(pos);

	Camera mainCam(fovy, aspect, n, f, eye, at);

	modelManager.LoadObj(&mesh);
	shaderManager.CompileShader(&shader);
	shaderManager.LinkProgram(&shader);
	///Create RendererContext
	RenderContext renderContext;
	renderContext.renderGO = &gameObject;
	renderContext.renderCam = &mainCam;
	renderContext.renderShader = &shader;
	renderer.GetRenderContext() = renderContext;
	///Loop
	MyMath::Vector3 formerTrans = gameObject.GetTransform().GetTrans();
	float counter = 0;

	while(display.CheckState() != STATE::END)
	{
		renderer.Clear();

		MyMath::Vector3 formerRot = gameObject.GetTransform().GetRotate();
		gameObject.GetTransform().SetRotate(MyMath::Vector3(formerRot.x, counter, formerRot.z));

		//renderer.InitArrays();
		renderer.UpdateDrawInfo();
		renderer.DrawTest();
		//renderer.ShaderTest();
		//renderer.DrawTest();

		//gameObject.GetTransform().SetRotate(MyMath::Vector3(formerRot.x, formerRot.y + MyMath::PI/360, formerRot.z));

		//renderer.DrawCall();

		display.SwapBuffer();
		EventHandle(display.CheckEvent(), &(renderer.GetRenderContext()) );

		counter += MyMath::PI/180;
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

void EventHandle(EventInfo eventInfo, RenderContext *rc)
{
#define MOVGO true
	Camera *cam = rc->renderCam;
	GameObject *go = rc->renderGO;

	MyMath::Vector3 formerTrans = go->GetTransform().GetTrans();
	MyMath::Vector3 formerEYE = cam->GetEYE();
	if (eventInfo.eventType == SDL_KEYDOWN)
	{
		switch (eventInfo.eventData)
		{
		case 'w':
#if MOVGO
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x, formerTrans.y, formerTrans.z - 0.1f));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x, formerEYE.y, formerEYE.z - 0.1f));
#endif
			break;
		case 's':
#if MOVGO
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x, formerTrans.y, formerTrans.z + 0.1f));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x, formerEYE.y, formerEYE.z + 0.1f));
#endif
			break;
		case 'a':
#if MOVGO			
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x - 0.1f, formerTrans.y, formerTrans.z));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x - 0.1f, formerEYE.y, formerEYE.z));
#endif
			break;
		case 'd':
#if MOVGO
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x + 0.1f, formerTrans.y, formerTrans.z));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x + 0.1f, formerEYE.y, formerEYE.z));
#endif
			break;
		}
		std::cout << eventInfo.eventData << std::endl;
	}
}
