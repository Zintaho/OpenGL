#include "Display.h"
#include "DisplayConstants.h"

#include <iostream>

Display::Display(DisplayOption option)
{
	this->winStat.title = TITLE;
	this->winStat.position = { WINDOW_POSX,WINDOW_POSY };
	this->winStat.size = { WINDOW_WIDTH, WINDOW_HEIGHT };
	this->winStat.displayOption = option;

	state = STATE::INIT;
}

void Display::InitSDL()
{	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)	//Initialize all of the SDL subsystems( ex) VIDEO, AUDIO, EVENTS, TIMER, JOYSTICK)
	{
		std::cerr << SDL_GetError() << std::endl;

		state = STATE::END;
		exit(1);
	}
}

void Display::SetSDLAttributes()
{
	///SET Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, VERSION_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, VERSION_MINOR);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, ON);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DEPTH_BIT_SIZE);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, COLOR_BIT_SIZE);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, COLOR_BIT_SIZE);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, COLOR_BIT_SIZE);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, COLOR_BIT_SIZE);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, MIN_FRAMEBUFFER_SIZE);
	///Get Display Flags
	displayFlags = GetDisplayFlags();

	///Other Options
	if (this->winStat.displayOption.ADAPTIVE_VSYNC)
	{
		if (SDL_GL_SetSwapInterval(ON) == -1)
		{///if adaptive vsync not supported
			std::cerr << "ADAPTIVE VSYNC NOT SUPPORTED" << std::endl;
			SDL_GL_SetSwapInterval(OFF);
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(OFF);
	}
}

Uint32 Display::GetDisplayFlags() const
{
	Uint32 flags = 0;
	flags |= SDL_WINDOW_OPENGL;
	if (this->winStat.displayOption.FULL_SCREEN) { flags |= SDL_WINDOW_FULLSCREEN; }
	if (this->winStat.displayOption.FULL_SCREEN_CUR_RESOLUTION) { flags |= SDL_WINDOW_FULLSCREEN_DESKTOP; }
	if (this->winStat.displayOption.VISIBLE) { flags |= SDL_WINDOW_SHOWN; }
	else { flags |= SDL_WINDOW_HIDDEN; }
	if (this->winStat.displayOption.BORDERLESS) { flags |= SDL_WINDOW_BORDERLESS; }
	if (this->winStat.displayOption.RESIZABLE) { flags |= SDL_WINDOW_RESIZABLE; }
	if (this->winStat.displayOption.MINIMIZED) { flags |= SDL_WINDOW_MINIMIZED; }
	if (this->winStat.displayOption.MAXIMIZED) { flags |= SDL_WINDOW_MAXIMIZED; }
	if (this->winStat.displayOption.INPUT_GRABBED) { flags |= SDL_WINDOW_INPUT_GRABBED; }
	if (this->winStat.displayOption.INPUT_FOCUS) { flags |= SDL_WINDOW_INPUT_FOCUS; }
	if (this->winStat.displayOption.MOUSE_FOCUS) { flags |= SDL_WINDOW_MOUSE_FOCUS; }
	if (this->winStat.displayOption.MOUSE_CAPTURE) { flags |= SDL_WINDOW_MOUSE_CAPTURE; }
	if (this->winStat.displayOption.HIGH_DPI) { flags |= SDL_WINDOW_ALLOW_HIGHDPI; }

	return flags;
}

void Display::CreateDisplay()
{
	InitSDL();
	SetSDLAttributes();

	window = SDL_CreateWindow(winStat.title.c_str(), winStat.position.x, winStat.position.y, winStat.size.x, winStat.size.y, displayFlags);
	glContext = SDL_GL_CreateContext(window);

	state = STATE::RUNNING;
}

void Display::SwapBuffer() const
{
	SDL_GL_SwapWindow(window);
}

void Display::CheckEvent()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			state = STATE::END;
			break;
		case SDL_KEYUP:
			Log(LOG_KEY_UP);
			break;		
		case SDL_KEYDOWN:
			Log(LOG_KEY_DOWN);
			break;		
		case SDL_MOUSEBUTTONUP:
			Log(LOG_MOUSE_UP);
			break;
		case SDL_MOUSEBUTTONDOWN:
			Log(LOG_MOUSE_DOWN);
			break;

		}
	}
}

void Display::Log(const char* log) const
{
	std::cout << log << std::endl;
}

Display::~Display()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}