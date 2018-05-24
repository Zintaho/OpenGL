/*
OpenGL 4.3 Practice
by Zintaho (YU Jin-seok)

from 2018-04
 now 2018-05

[TODO : MAIN]
텍스쳐
테셀레이션

[TODO : SUB]
마우스 이벤트 처리
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
	Mesh mesh("Trophy");
	Mesh *pMesh = &mesh;
	Shader shader(VS_PHONG, FS_PHONG);
	Shader shader2("VS", "FS", "TCS", "TES");
	Shader *pShader = &shader;

	MyMath::Vector3 pos(0, 0, 0.0f);
	MyMath::Vector3 rot(0, MyMath::PI/2, 0);
	MyMath::Vector3 scale(8.0f, 8.0f, 8.0f);
	Transform transform(pos, rot, scale);

	GameObject gameObject(pMesh, transform);
	GameObject *pGameObject = &gameObject;

	float fovy = (2.0f / 3.0f) * MyMath::PI;
	float aspect = display.GetAspect();
	float n = 1;
	float f = 1000;
	MyMath::Vector3 eye(0.0f, 0.0f, 3.0f);
	MyMath::Vector3 at(pos);

	Camera mainCam(fovy, aspect, n, f, eye, at);
	Camera *pCam = &mainCam;

	modelManager.LoadObj(pMesh);
	shaderManager.CompileShader(pShader);
	shaderManager.LinkProgram(pShader);
	///Create RendererContext
	RenderContext renderContext;
	renderContext.renderGO = pGameObject;
	renderContext.renderCam = pCam;
	renderContext.renderShader = pShader;
	renderer.GetRenderContext() = renderContext;
	///Loop
	MyMath::Vector3 formerTrans = gameObject.GetTransform().GetTrans();
	float counter = 0;

	while(display.CheckState() != STATE::END)
	{
		renderer.Clear();

		MyMath::Vector3 formerRot = gameObject.GetTransform().GetRotate();
		//gameObject.GetTransform().SetRotate(MyMath::Vector3(counter, counter, formerRot.z));

		renderer.InitArrays();
		renderer.UpdateDrawInfo();
		renderer.DrawCall();

		display.SwapBuffer();
		EventHandle(display.CheckEvent(), &(renderer.GetRenderContext()) );

		counter += MyMath::PI/180;
	}

	return 0;
}

void EventHandle(EventInfo eventInfo, RenderContext *rc)
{
#define MOVGO false
	Camera *cam = rc->renderCam;
	GameObject *go = rc->renderGO;
	const float speed = 0.5f;


	MyMath::Vector3 formerTrans = go->GetTransform().GetTrans();
	MyMath::Vector3 formerEYE = cam->GetEYE();
	if (eventInfo.eventType == SDL_KEYDOWN)
	{
		switch (eventInfo.eventData)
		{
		case 'w':
#if MOVGO
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x, formerTrans.y, formerTrans.z - speed));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x, formerEYE.y, formerEYE.z - speed));
#endif
			break;
		case 's':
#if MOVGO
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x, formerTrans.y, formerTrans.z + speed));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x, formerEYE.y, formerEYE.z + speed));
#endif
			break;
		case 'a':
#if MOVGO			
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x - speed, formerTrans.y, formerTrans.z));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x - speed, formerEYE.y, formerEYE.z));
#endif
			break;
		case 'd':
#if MOVGO
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x + speed, formerTrans.y, formerTrans.z));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x + speed, formerEYE.y, formerEYE.z));
#endif
			break;		
		case 'e':
#if MOVGO
				go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x , formerTrans.y - speed, formerTrans.z));
#else
				cam->SetEYE(MyMath::Vector3(formerEYE.x, formerEYE.y - speed, formerEYE.z));
#endif
				break;
		case 'q':
#if MOVGO
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x , formerTrans.y + speed, formerTrans.z));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x , formerEYE.y + speed, formerEYE.z));
#endif
			break;
		}
		std::cout << eventInfo.eventData << std::endl;
	}
}
