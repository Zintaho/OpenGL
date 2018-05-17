#include "Renderer.h"
#include "RendererConstants.h"

#include <iostream>

Renderer::Renderer(Display* display)
{
	this->display = display;

	InitGLEW();
	SetGLOptions();
}

void Renderer::InitGLEW()
{
	if (glewInit() != GLEW_OK)
	{///Initialization Failed
		std::cerr << "GLEW failed to initialize" << std::endl;
		exit(1);
	}

	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
}

void Renderer::SetGLOptions()
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

void Renderer::InitArrays()
{
	Mesh *mesh = renderContext.renderGO->GetMesh();
	size_t drawCount = mesh->GetIndice().size();

	GLsizei vertexSize = static_cast<GLsizei>(sizeof(Vertex));
	GLsizei numVertice = static_cast<GLsizei>(mesh->GetVertice().size());

	glGenVertexArrays(VAOTYPE(VAO_TYPE::NUM_VAO), VAOs);
	glBindVertexArray(VAOs[VAOTYPE(VAO_TYPE::MAIN)]);

	glGenBuffers(VBOTYPE(VBO_TYPE::NUM_VBO), VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOTYPE(VBO_TYPE::POS)]);
	glBufferData(GL_ARRAY_BUFFER, numVertice * vertexSize, &mesh->GetVertice()[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(VBOTYPE(VBO_TYPE::POS));
	glVertexAttribPointer(VBOTYPE(VBO_TYPE::POS), 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
	glEnableVertexAttribArray(VBOTYPE(VBO_TYPE::UV));
	glVertexAttribPointer(VBOTYPE(VBO_TYPE::UV), 2, GL_FLOAT, GL_FALSE, vertexSize, 0);
	glEnableVertexAttribArray(VBOTYPE(VBO_TYPE::NORMAL));
	glVertexAttribPointer(VBOTYPE(VBO_TYPE::NORMAL), 3, GL_FLOAT, GL_FALSE, vertexSize, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[VBOTYPE(VBO_TYPE::INDEX)]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawCount * sizeof(unsigned int), &mesh->GetIndice()[0], GL_STATIC_DRAW);
}

void Renderer::UpdateDrawInfo()
{
	GameObject *ro = renderContext.renderGO;
	Camera *rc = renderContext.renderCam;
	Shader *sh = renderContext.renderShader;

	glUseProgram(sh->GetProgram());

	MyMath::Matrix4x4 transMat = ro->GetTransform().MakeMatrix();
	MyMath::Matrix4x4 VPMat = rc->MakeMatrix();

	GLuint* uniforms = sh->GetUniforms();

	glUniformMatrix4fv(uniforms[static_cast<unsigned int>(UNIFORM_TYPE::TRANSFORM)], 1, GL_FALSE, transMat.GetMatrix());
	glUniformMatrix4fv(uniforms[static_cast<unsigned int>(UNIFORM_TYPE::VIEWPROJ)], 1, GL_FALSE, VPMat.GetMatrix());
	MyMath::Vector3 eye = rc->GetEYE();
	GLfloat fEye[3] = { eye.x,eye.y,eye.z };
	glUniform3fv(uniforms[static_cast<unsigned int>(UNIFORM_TYPE::VIEWPROJ)], 1, fEye);
}

void Renderer::DrawCall()
{
	Mesh *mesh = renderContext.renderGO->GetMesh();
	GLsizei drawCount = static_cast<GLsizei>(mesh->GetIndice().size());

	if (drawCount > 0)
	{
		glBindVertexArray(VAOs[0]);

		glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(NULL);
	}
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