#pragma once
#include <SDL2/SDL.H>
#include <string>
#include "MyColor.h"

class SDLWindow
{
public:
	SDLWindow(unsigned int width, unsigned int height, const std::string &title);
	virtual ~SDLWindow();

	void Update();
	bool CheckWindowClosed();
private:
	void Clear();

	const Color bgColor = { 0.0f, 0.0f, 0.5f, 1.0f };
	bool isWindowClosed;
	int status;

	SDL_Window * window;
	SDL_GLContext glContext;
};

