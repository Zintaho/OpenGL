/*
OpenGL 4.3 Practice
2018-04, Zintaho (Jin-Seok, Yu)
*/

//Header
///C++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
///OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
///User
#include "MyMath.h"
#include "main.h"
#include "C2.h"
#include "ShaderManager.h"

///to be erased
using namespace std;
//inline math functions
inline void cross3D(const float *u, const float *v, float* result)
{
	result[0] = u[1] * v[2] - u[2] * v[1];
	result[1] = u[2] * v[0] - u[0] * v[2];
	result[2] = u[0] * v[1] - u[1] * v[0];
}

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

			const int STRIDE = 6;
			Vertex vertice[8] =
			{
			{0.5f,  0.5f, 0.0f , 1.0f, 0.0f, 0.0f},		//R
			{-0.5f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f},	//G
			{0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f},		//B
			{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f},		//BL

			{0.5f,  0.5f, 1.0f , 1.0f, 1.0f, 0.0f},		//RG
			{-0.5f,  0.5f, 1.0f,	0.0f, 1.0f, 1.0f },	//GB
			{0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f },		//RB
			{- 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f }	//WHI
			};
			
			//unsigned int indice[36] =
			//{
			//	1,3,2,0,1,2,
			//	7,3,2,6,7,2,
			//	0,2,6,4,0,6,
			//	1,3,7,5,1,7,
			//	5,7,6,4,5,6,
			//	5,1,0,4,5,0,
			//};

			unsigned int indice[DRAW_AMOUNT] =
			{
				1,0,3,
				0,3,2,
				4,5,6,
				5,6,7,
			};

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
			{0.0f,1.0f,1.0f},	//EYE
			{0.0f,0.0f,0.5f},	//AT
			{0.0f,1.0f,0.0f},	//UP
			90,//fovy
			WINDOWY / WINDOWX,//aspect
			0,2//n,f
			};

			Matrix4x4 MVPmat;
			setViewMatrix(MVPmat, mainCam.EYE, mainCam.AT, mainCam.UP);

			for (int i = 0; i < 8; ++i)
			{
				//_EulerRotate(vertice[i].Pos, ROTY, 90);
				_multiply(MVPmat, vertice[i].Pos);
			}

			for (int i = 0; i < 8; ++i)
			{
				_PROJ(vertice[i].Pos, mainCam.fovy, mainCam.aspect, mainCam.f, mainCam.n);
			}

			//6. Set VertexArray , VertexBuffer, IndexBuffer
			unsigned int VAO, VBO, IBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertice), vertice, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice), indice, GL_STATIC_DRAW);
			///Pos
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			///Color
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			//glEnable(GL_CULL_FACE); //You MUST enable GL_CULL_FACE to use function glCullFace
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
				glDrawElements(GL_TRIANGLES, DRAW_AMOUNT, GL_UNSIGNED_INT, 0);

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

void _linearScale(float *pos, float a, float b, float c)
{
	float temp[3] = { 0 };

	float mat[3][3] =
	{
		a, 0, 0,
		0, b, 0,
		0, 0, c
	};

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			temp[y] += (mat[y][x] * pos[x]);
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		pos[i] = temp[i];
	}
}

void _translate(float *pos, float x, float y, float z)
{
	pos[0] += x;
	pos[1] += y;
	pos[2] += z;
}

void _EulerRotate(float *pos, int rot, float amount)
{
	amount *= (float)M_PI / 180.0f;

	float temp[4] = { 0 };
	float homoPos[4];
	for (int i = 0; i < 3; ++i) homoPos[i] = pos[i];
	homoPos[3] = 1;
	temp[3] = 1;
	float mat[4][4] = { 0 };
	switch (rot)
	{
	case ROTX:
		mat[1][1] = mat[2][2] = cos(amount);
		mat[1][2] = -sin(amount);
		mat[2][1] = sin(amount);
		mat[0][0] = 1;
		break;
	case ROTY:
		mat[0][0] = mat[2][2] = cos(amount);
		mat[2][0] = sin(amount);
		mat[0][2] = -sin(amount);
		mat[1][1] = 1;
		break;
	case ROTZ:
		mat[0][0] = mat[1][1] = cos(amount);
		mat[0][1] = -sin(amount);
		mat[1][0] = sin(amount);
		mat[2][2] = 1;
		break;
	}
	mat[3][3] = 1;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			temp[y] += (mat[y][x] * pos[x]);
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		pos[i] = temp[i];
	}
}

void _homoTransform(float *pos, float sx, float sy, float sz, float tx, float ty, float tz)
{
	float temp[4] = { 0 };
	float homoPos[4];
	for (int i = 0; i < 3; ++i) homoPos[i] = pos[i];
	homoPos[3] = 1;
	temp[3] = 1;
	float mat[4][4] = { 0 };

	mat[0][0] = sx;	mat[1][1] = sy;	mat[2][2] = sz; mat[3][3] = 1;
	mat[0][3] = tx * sx;	mat[1][3] = ty * sy;	mat[2][3] = tz * sz;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			temp[y] += (mat[y][x] * homoPos[x]);
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		pos[i] = temp[i];
	}
}

void _multiply(const float mat[4][4], float *pos)
{
	float temp[4] = { 0 };
	float homoPos[4];
	for (int i = 0; i < 3; ++i) homoPos[i] = pos[i];
	homoPos[3] = 1;
	temp[3] = 1;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			temp[y] += (mat[y][x] * homoPos[x]);
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		pos[i] = temp[i];
	}
}

void _PROJ(float *pos, float fovy, const float aspect, const float f, const float n)
{
	float temp[4] = { 0 };
	float homoPos[4];
	for (int i = 0; i < 3; ++i) homoPos[i] = pos[i];
	homoPos[3] = 1;
	temp[3] = 1;
	float mat[4][4] = { 0 };

	fovy *= (float)M_PI / 180.0f;

	mat[0][0] = -1 / (tan(fovy / 2) *aspect);
	mat[1][1] = -1 / (tan(fovy / 2));
	mat[2][2] = -((f + n) / (f - n));
	mat[2][3] = -2 * n*f / (f - n);
	mat[3][2] = -1;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			temp[y] += (mat[y][x] * homoPos[x]);
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		pos[i] = temp[i];
	}
}