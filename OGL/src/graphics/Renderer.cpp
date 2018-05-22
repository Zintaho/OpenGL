#include "Renderer.h"
#include "RendererConstants.h"

#include <iostream>

//more complex programs there are multiple buffers to store your various models and you must update the pipeline state with the buffer you intend to use.

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
	drawCount = static_cast<GLsizei>(mesh->GetIndice().size());

	GLsizei numVertice = static_cast<GLsizei>(mesh->GetVertice().size());
	GLsizei sizeofVertex = static_cast<GLsizei>(sizeof(Vertex));

	glGenVertexArrays(VAOTYPE(VAO_TYPE::NUM_VAO), VAOs);
	glBindVertexArray(VAOs[VAOTYPE(VAO_TYPE::MAIN)]);

	glGenBuffers(VBOTYPE(VBO_TYPE::NUM_VBO), VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOTYPE(VBO_TYPE::POS)]);
	glBufferData(GL_ARRAY_BUFFER, numVertice * sizeofVertex, &(mesh->GetVertice())[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VBOTYPE(VBO_TYPE::POS));
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOTYPE(VBO_TYPE::POS)]);
	glVertexAttribPointer(VBOTYPE(VBO_TYPE::POS), 3, GL_FLOAT, GL_FALSE, sizeofVertex, 0);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawCount * sizeof(unsigned int), &(mesh->GetIndice())[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
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

	glUniformMatrix4fv(uniforms[static_cast<unsigned int>(UNIFORM_TYPE::TRANSFORM)], 1, GL_TRUE, transMat.GetMatrix());
	glUniformMatrix4fv(uniforms[static_cast<unsigned int>(UNIFORM_TYPE::VIEWPROJ)], 1, GL_TRUE, VPMat.GetMatrix());

	MyMath::Vector3 eye = rc->GetEYE();
	GLfloat fEye[3] = { eye.x,eye.y,eye.z };
	glUniform3fv(uniforms[static_cast<unsigned int>(UNIFORM_TYPE::EYE)], 1, fEye);
}

void Renderer::DrawCall()
{
	if (drawCount > 0)
	{
		glBindVertexArray(VAOs[VAOTYPE(VAO_TYPE::MAIN)]);

		glDrawElements(GL_TRIANGLES,drawCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(NULL);
	}
}

Renderer::~Renderer()
{
}

///For Debug (under OGL3.2)
void Renderer::DrawTest()
{
	GLuint VBO;
	MyMath::Vector3 test[4];
	test[0] = MyMath::Vector3(-1.0f, -1.0f, 0.0f);
	test[1] = MyMath::Vector3(0.0f, -1.0f, 1.0f);
	test[2] = MyMath::Vector3(1.0f, -1.0f, 0.0f);
	test[3] = MyMath::Vector3(0.0f, 1.0f, 0.0f);

	GLuint IBO;
	unsigned int Indices[] = { 0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 };

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(test), test, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
}
