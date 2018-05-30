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
enum class TEX_TYPE : GLuint
{
	MAIN = 0,

	NUM_TEX
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
constexpr GLuint CONVERT(TEX_TYPE type)
{
	return static_cast<GLuint>(type);
}

struct TextureFilter
{
	GLint minFilter;
	GLint maxFilter;
};

struct RenderContext
{
	GameObject *renderGO;
	Camera *renderCam;
	Shader *renderShader;
	TextureFilter texFilter;
};

class Renderer
{
public:
	///Constructor, Destructor
	Renderer(Display* display);
	virtual ~Renderer();
	///Methods
	void SetRenderGO(GameObject *renderGO);
	inline void SetRenderCam(Camera *renderCam) { renderContext.renderCam = renderCam; }
	inline void SetRenderShader(Shader *renderShader) { renderContext.renderShader = renderShader; }
	inline void SetTextureFilter(TextureFilter texFilter) { renderContext.texFilter = texFilter; }
	inline GameObject* GetRenderGO() { return renderContext.renderGO; }
	inline Camera* GetRenderCam() { return renderContext.renderCam; }
	inline Shader* GetRenderShader() { return renderContext.renderShader; }
	inline TextureFilter GetTextureFilter() { return renderContext.texFilter; }
	void Clear();
	void GenRenderObjects();
	void UpdateUniform(UNIFORM_TYPE uniType);
	void UpdateUniforms();
	void UpdateTextures();
	void DrawCall();
	void DrawTest();
	void DrawTest(float f);
private:
	///Methods
	void InitGLEW();
	void SetGLOptions();
	void UpdateBufferData();
	///Members
	GLuint VAOs[CONVERT(VAO_TYPE::NUM_VAO)];
	GLuint VBOs[CONVERT(VBO_TYPE::NUM_VBO)];
	GLuint IBOs[CONVERT(IBO_TYPE::NUM_IBO)];
	GLuint Texs[CONVERT(TEX_TYPE::NUM_TEX)];

	Display *display;
	RenderContext renderContext; ///You cannot access renderContext directly by public methods
	GLsizei drawCount;
};