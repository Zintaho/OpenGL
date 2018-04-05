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

//ShaderSource
string vertexShaderSource;
string fragmentShaderSource;
void _loadShaderSource();
void _checkShaderCompileError(const unsigned int shader, string tag);
void _checkProgramLinkError(const unsigned int program, string tag);

int main()
{
	const int XSIZ = 800;
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

			//5. Setup Vertex Data
			const int STRIDE = 6;
			struct Vertex
			{
				float Pos[3];
				float Color[3];
			};
			Vertex vertice[4] =
			{
			{-0.5f,  0.5f, 0.0f , 1.0f, 0.0f, 0.0f},	// TopLeft | RED
			{0.5f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f},		// TopRight | GREEN
			{0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f},		// BtmRight | BLUE
			{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f}		// BtmLeft | BLACK
			};
			unsigned int indice[6] =
			{
				0, 1, 3,  // first Triangle
				1, 2, 3   // second Triangle
			};
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
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
