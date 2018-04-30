/*
OpenGL 4.3 Practice
2018-04, Zintaho (Jin-Seok, Yu)

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

///C++
#include <iostream>
#include <string>
#include <vector>
///OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
///User
#include "MyMath.h"
#include "Vertex.h"
#include "GameObject.h"
#include "main.h"
#include "C2.h"
#include "ShaderManager.h"
#include "ModelManager.h"

///to be erased
using namespace std;

int main()
{
	using namespace MyMath;

	//1. Initialize GLFW
	if (not glfwInit())
	{///Initialization Failed
		exit(EXIT_FAILURE);
	}
	else
	{
		//2. Create and Set Window
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR); //OpenGL 4.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Need not Older OpenGL

		GLFWwindow* window;
		window = glfwCreateWindow(WINDOWX, WINDOWY, TITLE, NULL, NULL);
		if (window == nullptr)
		{///Window or OpenGL context creation failed
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		else
		{
			//3.MakeContext, GLAD
			glfwMakeContextCurrent(window);
			if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				//failed to initialize GLAD
				glfwTerminate();
				exit(EXIT_FAILURE);
			}

			//4.Load Shader Program
			string vshaderFilename = FILENAME_VSHADER;
			string fshaderFilename = FILENAME_FSHADER;
			ShaderManager::LoadShaderSource(vshaderFilename, fshaderFilename);
			///vertex
			unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
			vector<char> compatibleVSource(ShaderManager::vertexShaderSource.begin(), ShaderManager::vertexShaderSource.end());
			compatibleVSource.push_back('\0');
			const char *ptr = &compatibleVSource[0];
			glShaderSource(vertexShader, 1, &ptr, NULL);
			glCompileShader(vertexShader);
			_checkShaderCompileError(vertexShader, "Vertex");
			///fragment			
			unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			vector<char> compatibleFSource(ShaderManager::fragmentShaderSource.begin(), ShaderManager::fragmentShaderSource.end());
			compatibleFSource.push_back('\0');
			ptr = &compatibleFSource[0];
			glShaderSource(fragmentShader, 1, &ptr, NULL);
			glCompileShader(fragmentShader);
			_checkShaderCompileError(fragmentShader, "Fragment");
			///link program
			int shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);
			glLinkProgram(shaderProgram);
			_checkProgramLinkError(shaderProgram, "Shader Program");
			///delete shader
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			//5. MVP Transformation
			string objectType = MORITAKA;
			GameObject myObject(objectType);
			ModelManager::ProcessObject(myObject);

			GLsizei vertexAmount = static_cast<GLsizei>(ModelManager::vertice.size());
			GLsizei drawAmount = static_cast<GLsizei>(ModelManager::indice.size());

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
			WINDOWY / WINDOWX,//aspect
			-1,1//n,f
			};

			mainCam.EYE.x = myObject.position.x + 0.5f;
			mainCam.EYE.y = myObject.position.y + 0.5f;
			mainCam.EYE.z = myObject.position.z + 2.0f;

			mainCam.AT.x = myObject.position.x;
			mainCam.AT.y = myObject.position.y;
			mainCam.AT.z = myObject.position.z;

			Matrix4x4 translateMat = { 0 };
			setTranslateMatrix(translateMat, transX, transY, transZ);

			Matrix4x4 scaleMat = { 0 };
			setScaleMatrix(scaleMat, scaleX, scaleY, scaleZ);

			Matrix4x4 viewMat = { 0 };
			setViewMatrix(viewMat, mainCam.EYE, mainCam.AT, mainCam.UP);

			Matrix4x4 projMat = { 0 };
			setProjMatrix(projMat, mainCam.fovy, mainCam.aspect, mainCam.n, mainCam.f);

			for (int i = 0; i < vertexAmount; ++i)
			{
				ModelManager::vertice[i].Pos = MultiplyMatVec(scaleMat, ModelManager::vertice[i].Pos);
				ModelManager::vertice[i].Pos = MultiplyMatVec(translateMat, ModelManager::vertice[i].Pos);
				ModelManager::vertice[i].Pos = MultiplyMatVec(viewMat, ModelManager::vertice[i].Pos);
				ModelManager::vertice[i].Pos = MultiplyMatVec(projMat, ModelManager::vertice[i].Pos);
			}
			
			//6. Set VertexArray , VertexBuffer, IndexBuffer

			size_t vCount = sizeof(Vertex) * drawAmount;
			size_t iCount = sizeof(int) * drawAmount;

			//6. Set VertexArray , VertexBuffer, IndexBuffer
			unsigned int VAO, VBO, IBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vCount, &ModelManager::vertice[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, iCount, &ModelManager::indice[0], GL_STATIC_DRAW);
			///Pos
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			glEnable(GL_CULL_FACE); //You MUST enable GL_CULL_FACE to use function glCullFace
			glDepthRange(0, 1);
			/// Loop
			while (!glfwWindowShouldClose(window))
			{
				///Input

				///Render
				glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				glUseProgram(shaderProgram);
				glBindVertexArray(VAO);
				glCullFace(GL_BACK);
				glDrawElements(GL_TRIANGLES, drawAmount, GL_UNSIGNED_INT, 0);

				///SwapBuffers, ProcessEvents
				glfwSwapBuffers(window);
				glfwPollEvents();
			}

			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &IBO);
		}

		glfwTerminate();
	}
	return 0;
}

void _checkShaderCompileError(const unsigned int shader, string tag)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << tag << ":: SHADER COMPILE ERROR\n" << infoLog << endl;
	}
}

void _checkProgramLinkError(const unsigned int program, string tag)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		cout << tag << ":: PROGRAM LINK ERROR\n" << infoLog << endl;
	}
}