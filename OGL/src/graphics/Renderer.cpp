#include "Renderer.h"
#include "RendererConstants.h"

#include <iostream>

Renderer::Renderer()
{
	InitGLEW();
	SetGLOptions();
}

void Renderer::InitGLEW() const
{
	if (glewInit() != GLEW_OK)
	{///Initialization Failed
		std::cerr << "GLEW failed to initialize" << std::endl;
		exit(1);
	}

	std::cout << "Current GL Version: " << glGetString(GL_VERSION) << std::endl;
}

void Renderer::SetGLOptions() const
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
}

void Renderer::Clear()
{
	glClearColor(COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Renderer::~Renderer()
{

}

///For Debug (under OGL3.2)
void Renderer::DrawTriangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
}