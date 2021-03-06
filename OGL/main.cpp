/*
OpenGL 4.3 Practice
by Zintaho (YU Jin-seok)

from 2018-04
 now 2018-05

[TODO : MAIN]
테셀레이션(PN-Triangle) //TCS, TES는 적용 가능
애니메이션

[TODO : SUB]
마우스 이벤트 처리
파일 로딩 속도
글로벌 일루미네이션

[TODO : MISC]
*/

//Header
#include "MainConstants.h"
#include "src/core/Display.h"
#include "src/graphics/Renderer.h"
#include "src/graphics/ModelManager.h"
#include "src/graphics/ShaderManager.h"

void EventHandle(EventInfo eventInfo, Renderer &renderer);

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
	///Process Meshes
	Mesh mesh("Rabbit", GL_PATCHES);
	Mesh *pMesh = &mesh;
	modelManager.LoadObj(pMesh);
	///Process Textures
	Texture texture("test", "bmp");
	Texture *pTexture = &texture;
	///Process Shaders
	Shader shader2("VS_PHONG", "FS_PHONG");
	Shader shader2_2("VS", "FS");
	Shader shader3("vertex", "fragment", "geometry");
	Shader shader4("VS", "FS", "GS", "TCS", "TES");
	Shader *pShader = &shader4;
	shaderManager.ProcessShader(pShader);
	///Create GameObjects
	std::vector<GameObject> vecGO;
	MyMath::Vector3 pos(0, 0, 0.0f);
	MyMath::Vector3 rot(0, MyMath::PI, 0);
	MyMath::Vector3 scale(10.0f, 10.0f, 10.0f);
	Transform transform(pos, rot, scale);
	for (int i = 0; i < OBJECTS; ++i)
	{
		vecGO.push_back(GameObject(pMesh, transform));
		vecGO[i].SetTexture(pTexture);
		transform.SetTrans(MyMath::Vector3(transform.GetTrans().x + 2.0f, 0.0f, 0.0f));
	}
	///Create Cameras
	float fovy = (2.0f / 3.0f) * MyMath::PI;
	float aspect = display.GetAspect();
	float n = 1;
	float f = 1000;
	MyMath::Vector3 eye(0.0f, 0.0f, 3.0f);
	MyMath::Vector3 at(pos);
	Camera mainCam(fovy, aspect, n, f, eye, at);
	Camera *pCam = &mainCam;
	///Set RenderContext
	renderer.SetTextureFilter({ GL_LINEAR,GL_LINEAR });
	renderer.SetRenderCam(pCam);
	renderer.SetRenderShader(pShader);
	renderer.SetRenderGO(&vecGO[0]);

	///Loop
	float counter = 0;
	while (display.CheckState() != STATE::END)
	{
		renderer.Clear();

		renderer.UpdateUniform(UNIFORM_TYPE::VIEW);
		renderer.UpdateUniform(UNIFORM_TYPE::PROJ);

		renderer.DrawCall();

		display.SwapBuffer();
		EventHandle(display.CheckEvent(), renderer);

		counter += MyMath::PI / 180;
	}

	///END
	return 0;
}

void EventHandle(EventInfo eventInfo, Renderer &renderer)
{
#define MOVGO false
	Camera *cam = renderer.GetRenderCam();
	GameObject *go = renderer.GetRenderGO();
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
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x, formerTrans.y - speed, formerTrans.z));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x, formerEYE.y - speed, formerEYE.z));
#endif
			break;
		case 'q':
#if MOVGO
			go->GetTransform().SetTrans(MyMath::Vector3(formerTrans.x, formerTrans.y + speed, formerTrans.z));
#else
			cam->SetEYE(MyMath::Vector3(formerEYE.x, formerEYE.y + speed, formerEYE.z));
#endif
			break;
		}
		std::cout << eventInfo.eventData << std::endl;
	}
}
