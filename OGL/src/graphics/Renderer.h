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
	POS = 0,
	//UV,
	//NORMAL,

	NUM_VBO
};

constexpr GLuint VAOTYPE(VAO_TYPE type)
{
	return static_cast<GLuint>(type);
}
constexpr GLuint VBOTYPE(VBO_TYPE type)
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
	void InitArrays();
	void UpdateDrawInfo();
	void DrawCall();
	void DrawTest();
private:
	///Methods
	void InitGLEW();
	void SetGLOptions();
	///Membersx	
	unsigned int VAOs[static_cast<GLuint>(VAO_TYPE::NUM_VAO)];
	unsigned int VBOs[static_cast<GLuint>(VBO_TYPE::NUM_VBO)];
	unsigned int IBO;

	Display *display;
	RenderContext renderContext;
	GLsizei drawCount;
};