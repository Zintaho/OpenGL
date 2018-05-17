#pragma once
#include <../../include/GL/glew.h>
#include "../../src/core/Display.h"
#include "GameObject.h"
#include "Camera.h"

struct RenderContext
{
	GameObject *renderGO;
	GameObject *renderCam;
};

class Renderer
{
public:
	///Constructor, Destructor
	Renderer(Display* display);
	virtual ~Renderer();
	///Methods
	inline RenderContext &GetRenderContext() { return renderContext; }

	void Clear();

	void DrawTest();
private:
	///Methods
	void InitGLEW() const;
	void SetGLOptions() const;
	///Members
	Display *display;
	RenderContext renderContext;
};