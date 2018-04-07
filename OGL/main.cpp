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
#define _USE_MATH_DEFINES
#include <math.h>
///OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
///User
#include "C2.h"
///namespace
using namespace std;

//inline CallBackFunctions
inline static void errorCallback(int error, const char* description)
{
	cerr << "Error : " << description << '\n';
}
inline static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
inline static void fbSizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
//inline math functions
inline void cross3D(const float *u, const float *v, float* result)
{
	result[0] = u[1] * v[2] - u[2] * v[1];
	result[1] = u[2] * v[0] - u[0] * v[2];
	result[2] = u[0] * v[1] - u[1] * v[0];
}

//ShaderSource
string vertexShaderSource;
string fragmentShaderSource;

int main()
{
	const int XSIZ = 600;
	const int YSIZ = 600;
	const char* TITLE = "OpenGL 4.3 Practice";
	//1. Initialize GLFW
	if (not glfwInit())
	{///Initialization Failed
		exit(EXIT_FAILURE);
	}
	else
	{
		//2. Create and Set Window
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(XSIZ, YSIZ, TITLE, NULL, NULL);
		if (not window)
		{///Window or OpenGL context creation failed
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		else
		{
			//3.MakeContext and SetCallback, GLAD
			glfwMakeContextCurrent(window);

			glfwSetErrorCallback(errorCallback);
			glfwSetKeyCallback(window, keyCallback);
			glfwSetFramebufferSizeCallback(window, fbSizeCallBack);

			if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				//failed to initialize GLAD
				glfwTerminate();
				exit(EXIT_FAILURE);
			}
			//4.Load Shader Program
			_loadShaderSource();
			///vertex
			unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
			vector<char> compatibleVSource(vertexShaderSource.begin(), vertexShaderSource.end());
			compatibleVSource.push_back('\0');
			const char *ptr = &compatibleVSource[0];
			glShaderSource(vertexShader, 1, &ptr, NULL);
			glCompileShader(vertexShader);
			_checkShaderCompileError(vertexShader, "Vertex");
			///fragment			
			unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			vector<char> compatibleFSource(fragmentShaderSource.begin(), fragmentShaderSource.end());
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
			struct Vertex
			{
				float Pos[3];
				float Color[3];
			};
			struct Camera
			{
				float EYE[3];
				float AT[3];
				float UP[3];
				float fovy;
				float aspect;
				float f, n;
			};

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
			
			unsigned int indice[36] =
			{
				1,3,2,0,1,2,
				7,3,2,6,7,2,
				0,2,6,4,0,6,
				1,3,7,5,1,7,
				5,7,6,4,5,6,
				5,1,0,4,5,0,
			};
			Camera mainCam =
			{
			{0.3f,0.6f,1.0f},	//EYE
			{0.0f,0.0f,0.5f},	//AT
			{0.0f,1.0f,0.0f},	//UP
			120,//fovy
			YSIZ / XSIZ,//aspect
			-1,1//f,n
			};
			float MVPmat[4][4];
			_setVIEW(MVPmat, mainCam.EYE, mainCam.AT, mainCam.UP);
			for (int i = 0; i < 8; ++i)
			{
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

			/// Loop
			while (!glfwWindowShouldClose(window))
			{
				///Input

				///Render
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				glUseProgram(shaderProgram);
				glBindVertexArray(VAO);
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

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

void _loadShaderSource()
{
	///Load Shader Source
	string temp;
	ifstream source(".\\shader\\vertex.glsl");
	while (not source.eof())
	{
		getline(source, temp);
		vertexShaderSource += (temp + '\n');
	}
	source.close();
	source.open(".\\shader\\fragment.glsl");
	while (not source.eof())
	{
		getline(source, temp);
		fragmentShaderSource += (temp + '\n');
	}
	source.close();
	///
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
		mat[0][2] = sin(amount);
		mat[2][0] = -sin(amount);
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

void _setVIEW(float mat[4][4], const float *EYE, const float *AT, const float *UP)
{
	for (int z = 0; z < 3; ++z) mat[3][z] = 0;
	mat[3][3] = 1;

	float u[3], v[3], n[3];
	for (int i = 0; i < 3; ++i)
	{
		n[i] = (EYE[i] - AT[i]);
	}
	if (not (n[0] == 0 && n[1] == 0 && n[2] == 0))
	{
		for (int i = 0; i < 3; ++i)
		{
			n[i] /= sqrt((n[0] * n[0] + n[1] * n[1] + n[2] * n[2]));
		}
	}
	cross3D(n, UP, u);
	if (not (u[0] == 0 && u[1] == 0 && u[2] == 0))
	{
		for (int i = 0; i < 3; ++i)
		{
			u[i] /= sqrt((u[0] * u[0] + u[1] * u[1] + u[2] * u[2]));
		}
	}
	cross3D(n, u, v);

	for (int i = 0; i < 3; ++i)
	{
		mat[0][i] = u[i];
		mat[1][i] = v[i];
		mat[2][i] = n[i];
	}
	mat[0][3] = -EYE[0] * (u[0] + u[1] + u[2]);
	mat[1][3] = -EYE[1] * (v[0] + v[1] + v[2]);
	mat[2][3] = -EYE[2] * (n[0] + n[1] + n[2]);
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