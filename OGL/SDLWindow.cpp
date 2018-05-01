#include "SDLWindow.h"

#include <GLFW/glfw3.h>
#include <iostream>

SDLWindow::SDLWindow(unsigned int width, unsigned int height, const std::string &title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);	//each color size is 8-bit;
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(window);

	//1. Initialize GLFW
	status = glfwInit();

	if (status == GLFW_NOT_INITIALIZED)
	{///Initialization Failed
		std::cerr << "GLFW failed to initialize" << std::endl;
	}
	isWindowClosed = false;
}


SDLWindow::~SDLWindow()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void SDLWindow::Update()
{
	Clear();
	SDL_GL_SwapWindow(window);
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isWindowClosed = true;
		}
	}
}

void SDLWindow::Clear()
{
	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool SDLWindow::CheckWindowClosed()
{
	return isWindowClosed;
}
