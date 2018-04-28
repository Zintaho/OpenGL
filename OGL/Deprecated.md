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


			//glfwSetErrorCallback(errorCallback);
			//glfwSetKeyCallback(window, keyCallback);
			//glfwSetFramebufferSizeCallback(window, fbSizeCallBack);


			

void _loadShaderSource()
{
	using namespace std;
	///Load Shader Source
	string buffer;
	ifstream source(".\\shader\\vertex.glsl");
	while (not source.eof())
	{
		getline(source, buffer);
		ShaderManager::vertexShaderSource += (buffer + '\n');
	}
	source.close();
	source.open(".\\shader\\fragment.glsl");
	while (not source.eof())
	{
		getline(source, buffer);
		ShaderManager::fragmentShaderSource += (buffer + '\n');
	}
	source.close();
	///
}