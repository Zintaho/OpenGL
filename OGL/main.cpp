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

int WinMain(int argc, char **argv)
{
	SDLWindow sdlWindow(WINDOW_POSX,WINDOW_POSY,WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);

	Vertex vertice[4];
	vertice[0].Pos = { 0.5f,0.5f,0.5f };
	vertice[1].Pos = { -0.5f,0.5f,0.5f };
	vertice[2].Pos = { -0.5f,-0.5f,0.5f };
	vertice[3].Pos = { 0.5f,-0.5f,0.5f };

	Mesh mesh(vertice, 4);
	
	while (not sdlWindow.CheckWindowClosed())
	{
		sdlWindow.Clear();
		ShaderManager::LoadShader(FILENAME_VSHADER, FILENAME_FSHADER);

		mesh.DrawMesh();

		sdlWindow.Update();
		ShaderManager::UnloadShader();
	}




	//		//5. MVP Transformation
	//		string objectType = DUNNO;
	//		GameObject myObject(objectType);
	//		ModelManager::ProcessObject(myObject);

	//		GLsizei vertexAmount = static_cast<GLsizei>(ModelManager::vertice.size());
	//		GLsizei drawAmount = static_cast<GLsizei>(ModelManager::indice.size());

	//		struct Camera2
	//		{
	//			Vector3 EYE;
	//			Vector3 AT;
	//			Vector3 UP;
	//			float fovy;
	//			float aspect;
	//			float n, f;
	//		};

	//		Camera2 mainCam =
	//		{
	//		{0.0f,0.0f,2.0f},	//EYE
	//		{0.0f,0.0f,0.5f},	//AT
	//		{0.0f,1.0f,0.0f},	//UP
	//		120,//fovy
	//		WINDOWY / WINDOWX,//aspect
	//		-1,1//n,f
	//		};

	//		mainCam.EYE.x = myObject.position.x + 0.5f;
	//		mainCam.EYE.y = myObject.position.y + 0.5f;
	//		mainCam.EYE.z = myObject.position.z + 2.0f;

	//		mainCam.AT.x = myObject.position.x;
	//		mainCam.AT.y = myObject.position.y;
	//		mainCam.AT.z = myObject.position.z;

	//		Matrix4x4 translateMat = { 0 };
	//		setTranslateMatrix(translateMat, transX, transY, transZ);

	//		Matrix4x4 scaleMat = { 0 };
	//		setScaleMatrix(scaleMat, scaleX, scaleY, scaleZ);

	//		Matrix4x4 viewMat = { 0 };
	//		setViewMatrix(viewMat, mainCam.EYE, mainCam.AT, mainCam.UP);

	//		Matrix4x4 projMat = { 0 };
	//		setProjMatrix(projMat, mainCam.fovy, mainCam.aspect, mainCam.n, mainCam.f);

	//		for (int i = 0; i < vertexAmount; ++i)
	//		{
	//			ModelManager::vertice[i].Pos = MultiplyMatVec(scaleMat, ModelManager::vertice[i].Pos);
	//			ModelManager::vertice[i].Pos = MultiplyMatVec(translateMat, ModelManager::vertice[i].Pos);
	//			ModelManager::vertice[i].Pos = MultiplyMatVec(viewMat, ModelManager::vertice[i].Pos);
	//			ModelManager::vertice[i].Pos = MultiplyMatVec(projMat, ModelManager::vertice[i].Pos);
	//		}


	//		glEnable(GL_CULL_FACE); //You MUST enable GL_CULL_FACE to use function glCullFace
	//		glDepthRange(0, 1);
	//		/// Loop
	//		while (!glfwWindowShouldClose(window))
	//		{
	//			///Input

	//			///Render
	//			glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	//			glClear(GL_COLOR_BUFFER_BIT);

	//			glUseProgram(shaderProgram);
	//			glBindVertexArray(VAO);
	//			glCullFace(GL_BACK);
	//			glDrawElements(GL_TRIANGLES, drawAmount, GL_UNSIGNED_INT, 0);

	//			///SwapBuffers, ProcessEvents
	//			glfwSwapBuffers(window);
	//			glfwPollEvents();
	//		}

	//		glDeleteVertexArrays(1, &VAO);
	//		glDeleteBuffers(1, &VBO);
	//		glDeleteBuffers(1, &IBO);
	//	}

	//	glfwTerminate();
	//}
	return 0;
}
