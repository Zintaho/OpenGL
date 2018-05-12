#pragma once
#include <../../include/GL/glew.h>
#include "../../src/core/Display.h"

class Renderer
{
public:
	///Constructor, Destructor
	Renderer(Display* display);
	virtual ~Renderer();
	///Methods
	void Clear();

	void DrawTest();
private:
	///Methods
	void InitGLEW() const;
	void SetGLOptions() const;
	///Members
	Display *display;
};