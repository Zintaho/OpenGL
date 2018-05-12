#pragma once
#include <../../include/SDL2/SDL.h>
#include <string>

struct Point2D
{
	int x, y;
};

struct DisplayOption
{
	///CREATE WINDOW FLAGS
	bool FULL_SCREEN;
	bool FULL_SCREEN_CUR_RESOLUTION;
	bool VISIBLE;
	bool RESIZABLE;
	bool BORDERLESS;
	bool MINIMIZED;
	bool MAXIMIZED;
	bool INPUT_GRABBED;
	bool INPUT_FOCUS;
	bool MOUSE_FOCUS;
	bool MOUSE_CAPTURE;
	bool HIGH_DPI;
	///OTHER OPTIONS
	bool ADAPTIVE_VSYNC;
};

struct WindowStatus
{
	std::string title;
	Point2D position;
	Point2D size;
	DisplayOption displayOption;
};

enum class STATE : Uint16
{
	END = 0,
	INIT,
	RUNNING,
	
	NUM_STATE
};

class Display
{
public:
	///Constructor, Destructor
	Display(DisplayOption option);
	virtual ~Display();
	///Methods
	void CreateDisplay();
	void SwapBuffer() const;
	void CheckEvent();

	inline STATE CheckState() const { return state; }
	///Members
private:
	///Methods
	void InitSDL();
	void SetSDLAttributes();
	Uint32 GetDisplayFlags() const;

	void Log(const char* log) const;
	///Members
	WindowStatus winStat;
	SDL_Window *window;
	SDL_GLContext glContext;
	Uint32 displayFlags;

	STATE state;
	SDL_Event event;
};

