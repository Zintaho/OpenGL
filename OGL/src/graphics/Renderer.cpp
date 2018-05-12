#include "Renderer.h"
#include "RendererConstants.h"

#include <iostream>

Renderer::Renderer(Display* display)
{
	this->display = display;

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

	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
}

void Renderer::SetGLOptions() const
{
	int w, h;
	SDL_GetWindowSize(&display->GetWindow(), &w, &h);

	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));

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
void Renderer::DrawTest()
{
	GLuint vao;
	int count = 1;
	glGenVertexArrays(count, &vao);
	glBindVertexArray(vao);

	glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
}