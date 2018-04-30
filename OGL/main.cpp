/*
OpenGL 4.3 Practice
2018-04, Zintaho (Jin-Seok, Yu)

[TODO : MAIN]
모델 로더 구현
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
			ShaderManager::LoadShaderSource(vshaderFilename,fshaderFilename);
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
			GameObject myObject(PAGODA);
			ModelManager::ProcessObject(myObject);

			GLsizei vertexAmount = static_cast<GLsizei>(ModelManager::vertice.size());
			GLsizei drawAmount = static_cast<GLsizei>(ModelManager::indice.size());
			const int STRIDE = 6;

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
			{0.2f,0.5f,1.0f},	//EYE
			{0.0f,0.0f,0.5f},	//AT
			{0.0f,1.0f,0.0f},	//UP
			120,//fovy
			WINDOWY / WINDOWX,//aspect
			-1,1//n,f
			};

			Matrix4x4 scaleMat = { 0 };
			setScaleMatrix(scaleMat, scaleX, scaleY, scaleZ);

			Matrix4x4 viewMat = { 0 };
			setViewMatrix(viewMat, mainCam.EYE, mainCam.AT, mainCam.UP);

			Matrix4x4 projMat = { 0 };
			setProjMatrix(projMat, mainCam.fovy, mainCam.aspect, mainCam.n, mainCam.f);

			for (int i = 0; i < vertexAmount; ++i)
			{
				ModelManager::vertice[i].Pos = MultiplyMatVec(scaleMat, ModelManager::vertice[i].Pos);
			}
			myObject.position.x *= scaleX;
			myObject.position.y *= scaleY;
			myObject.position.z *= scaleZ;

			mainCam.AT.x = myObject.position.x;
			mainCam.AT.y = myObject.position.y;
			mainCam.AT.z = myObject.position.z;

			Vertex *arrVertice = &ModelManager::vertice[0];

			//6. Set VertexArray , VertexBuffer, IndexBuffer

			GLuint VAO, VBO, IBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(arrVertice), arrVertice, GL_STATIC_DRAW);

			//pos
			glVertexAttribPointer(
				0,                  // 0번째 속성(attribute). 0 이 될 특별한 이유는 없지만, 쉐이더의 레이아웃(layout)와 반드시 맞추어야 합니다.
				3,                  // 크기(size)
				GL_FLOAT,           // 타입(type)
				GL_FALSE,           // 정규화(normalized)?
				3 * sizeof(float),                  // 다음 요소 까지 간격(stride)
				(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
			);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			glPointSize(5);
			/// Loop
			do
			{
				///Input

				///Render
				glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glUseProgram(shaderProgram);
				glBindVertexArray(VAO);
				glDrawArrays(GL_POINTS, 0, vertexAmount); // 버텍스 0에서 시작해서; 총 3개의 버텍스로 -> 하나의 삼각형


				///SwapBuffers, ProcessEvents
				glfwSwapBuffers(window);
				glfwPollEvents();

			}
			while (not glfwWindowShouldClose(window));

			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			//glDeleteBuffers(1, &IBO);
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