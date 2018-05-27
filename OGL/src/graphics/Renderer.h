#pragma once
#include <../../include/GL/glew.h>
#include "../../src/core/Display.h"
#include "GameObject.h"
#include "Camera.h"
#include "Shader.h"

enum class VAO_TYPE : GLuint
{
	MAIN = 0,

	NUM_VAO
};
enum class VBO_TYPE : GLuint
{
	MAIN = 0,

	NUM_VBO
};
enum class IBO_TYPE : GLuint
{
	MAIN = 0,

	NUM_IBO
};

constexpr GLuint CONVERT(VAO_TYPE type)
{
	return static_cast<GLuint>(type);
}
constexpr GLuint CONVERT(VBO_TYPE type)
{
	return static_cast<GLuint>(type);
}
constexpr GLuint CONVERT(IBO_TYPE type)
{
	return static_cast<GLuint>(type);
}


struct RenderContext
{
	GameObject *renderGO;
	Camera *renderCam;
	Shader *renderShader;
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
	void GenRenderObjects();
	void UpdateDrawInfo();
	void DrawCall();
	void DrawTest();
	void DrawTest(float f);
private:
	///Methods
	void InitGLEW();
	void SetGLOptions();
	///Membersx	
	unsigned int VAOs[CONVERT(VAO_TYPE::NUM_VAO)];
	unsigned int VBOs[CONVERT(VBO_TYPE::NUM_VBO)];
	unsigned int IBOs[CONVERT(IBO_TYPE::NUM_IBO)];

	Display *display;
	RenderContext renderContext;
	GLsizei drawCount;
};