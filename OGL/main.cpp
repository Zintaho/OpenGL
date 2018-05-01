/*
OpenGL 4.3 Practice
by Zintaho (Jin-Seok, Yu)

from 2018-04
 now 2018-05

[TODO : MAIN]
ī�޶� Ŭ����
�� �� ����

��ο� ���� (ArrayBuffer�� �ѵ��� �Ѿ�� crash - ���ڳ���׷��� ������ ����)

���� -> ���� ��Ʈ����

[TODO : SUB]
�� �δ� ����(�ӵ��� ����, uv��ǥ �о�;���, ��ֺ��� �о�;� ��)

[TODO : MISC]
��� ����
*/

//Header
#include "MainConstants.h"
#include "SDLWindow.h"
#include "ShaderManager.h"

int WinMain(int argc, char **argv)
{
	SDLWindow sdlWindow(WINDOW_POSX,WINDOW_POSY,WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
	
	while (not sdlWindow.CheckWindowClosed())
	{
		sdlWindow.Clear();
		ShaderManager::LoadShader(FILENAME_VSHADER, FILENAME_FSHADER);
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
	//		
	//		//6. Set VertexArray , VertexBuffer, IndexBuffer

	//		size_t vCount = sizeof(Vertex) * drawAmount;
	//		size_t iCount = sizeof(int) * drawAmount;

	//		//6. Set VertexArray , VertexBuffer, IndexBuffer
	//		unsigned int VAO, VBO, IBO;
	//		glGenVertexArrays(1, &VAO);
	//		glGenBuffers(1, &VBO);
	//		glGenBuffers(1, &IBO);

	//		glBindVertexArray(VAO);
	//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//		glBufferData(GL_ARRAY_BUFFER, vCount, &ModelManager::vertice[0], GL_STATIC_DRAW);

	//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, iCount, &ModelManager::indice[0], GL_STATIC_DRAW);
	//		///Pos
	//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//		glEnableVertexAttribArray(0);

	//		glBindBuffer(GL_ARRAY_BUFFER, 0);
	//		glBindVertexArray(0);

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
