#include "SDLWindow.h"
#include "RenderConstants.h"

#include <GL/glew.h>
#include <iostream>

SDLWindow::SDLWindow(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height, const std::string &title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);	//each color size is 8-bit;
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), posX, posY, width, height, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(window);

	//1. Initialize GLFW
	status = glewInit();

	if (status == GLEW_OK)
	{///Initialization Failed
		std::cerr << "GLEW failed to initialize" << std::endl;
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
	glClearColor(COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool SDLWindow::CheckWindowClosed()
{
	return isWindowClosed;
}
