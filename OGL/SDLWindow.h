#pragma once
#include <SDL2/SDL.H>
#include <string>

class SDLWindow
{
public:
	SDLWindow(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height, const std::string &title);
	virtual ~SDLWindow();

	void Update();
	void SwapBuffer();
	bool CheckWindowClosed();
	void Clear();
private:
	bool isWindowClosed;
	int status;

	SDL_Event event;
	SDL_Window * window;
	SDL_GLContext glContext;
};

