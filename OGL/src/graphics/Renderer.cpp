#include "Renderer.h"
#include "RendererConstants.h"

#include <iostream>

//more complex programs there are multiple buffers to store your various models and you must update the pipeline state with the buffer you intend to use.

Renderer::Renderer(Display* display)
{
	renderContext.renderGO = nullptr;
	renderContext.renderCam = nullptr;
	renderContext.renderShader = nullptr;
	this->display = display;

	InitGLEW();
	SetGLOptions();
	GenRenderObjects();
}

void Renderer::SetRenderGO(GameObject *renderGO)
{
	bool isSameMesh = false;
	if (renderContext.renderGO != nullptr)
	{
		Mesh *pMeshBefore = renderContext.renderGO->GetMesh();
		if (pMeshBefore != 0 && pMeshBefore == renderGO->GetMesh())
		{
			isSameMesh = true;
		}
	}
	renderContext.renderGO = renderGO;
	if (not isSameMesh)
	{
		UpdateBufferData();
	}
	UpdateUniforms();
	UpdateTextures();
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

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::Clear()
{
	glClearColor(COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::GenRenderObjects()
{
	glGenVertexArrays(CONVERT(VAO_TYPE::NUM_VAO), VAOs);
	glGenBuffers(CONVERT(VBO_TYPE::NUM_VBO), VBOs);
	glGenBuffers(CONVERT(IBO_TYPE::NUM_IBO), IBOs);
}

void Renderer::UpdateBufferData()
{
	Mesh *mesh = renderContext.renderGO->GetMesh();
	GLsizei numVertice = static_cast<GLsizei>(mesh->GetVertice().size());
	GLsizei sizeofVertex = static_cast<GLsizei>(sizeof(Vertex));
	drawCount = static_cast<GLsizei>(mesh->GetIndice().size());
	///Bind VAO
	glBindVertexArray(VAOs[CONVERT(VAO_TYPE::MAIN)]);
	///Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[CONVERT(VBO_TYPE::MAIN)]);
	glBufferData(GL_ARRAY_BUFFER, numVertice * sizeofVertex, &(mesh->GetVertice())[0], GL_STATIC_DRAW);
	glVertexAttribPointer(CONVERT(ATTRIB_TYPE::POS), 3, GL_FLOAT, GL_FALSE, sizeofVertex, 0);
	glEnableVertexAttribArray(CONVERT(ATTRIB_TYPE::POS));
	glVertexAttribPointer(CONVERT(ATTRIB_TYPE::UV), 2, GL_FLOAT, GL_FALSE, sizeofVertex, 0);
	glEnableVertexAttribArray(CONVERT(ATTRIB_TYPE::UV));
	glVertexAttribPointer(CONVERT(ATTRIB_TYPE::NORMAL), 3, GL_FLOAT, GL_TRUE, sizeofVertex, 0);
	glEnableVertexAttribArray(CONVERT(ATTRIB_TYPE::NORMAL));
	///Bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOs[CONVERT(IBO_TYPE::MAIN)]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawCount * sizeof(unsigned int), &(mesh->GetIndice())[0], GL_STATIC_DRAW);
}

void Renderer::UpdateUniforms()
{
	GameObject *ro = renderContext.renderGO;
	Camera *rc = renderContext.renderCam;
	Shader *sh = renderContext.renderShader;
	///Get ShaderProgram
	glUseProgram(sh->GetProgram());

	MyMath::Matrix4x4 transMat = ro->GetTransform().MakeMatrix();
	MyMath::Matrix4x4 viewMat = rc->MakeViewMatrix();
	MyMath::Matrix4x4 projMat = rc->MakeProjMatrix();
	GLuint* uniforms = sh->GetUniforms();

	glUniformMatrix4fv(uniforms[CONVERT(UNIFORM_TYPE::TRANSFORM)], 1, GL_TRUE, transMat.GetMatrix());
	glUniformMatrix4fv(uniforms[CONVERT(UNIFORM_TYPE::VIEW)], 1, GL_TRUE, viewMat.GetMatrix());
	glUniformMatrix4fv(uniforms[CONVERT(UNIFORM_TYPE::PROJ)], 1, GL_TRUE, projMat.GetMatrix());
	MyMath::Vector3 eye = rc->GetEYE();
	GLfloat fEye[3] = { eye.x,eye.y,eye.z };
	glUniform3fv(uniforms[CONVERT(UNIFORM_TYPE::EYE)], 1, fEye);
}

void Renderer::UpdateUniform(UNIFORM_TYPE uniType)
{
	Camera * rc = renderContext.renderCam;
	Shader *sh = renderContext.renderShader;
	glUseProgram(sh->GetProgram());

	GLuint* uniforms = sh->GetUniforms();
	switch (uniType)
	{
	case UNIFORM_TYPE::TRANSFORM:
	{
		MyMath::Matrix4x4 transMat = renderContext.renderGO->GetTransform().MakeMatrix();
		glUniformMatrix4fv(uniforms[CONVERT(UNIFORM_TYPE::TRANSFORM)], 1, GL_TRUE, transMat.GetMatrix());
		break;
	}
	case UNIFORM_TYPE::VIEW:
	{
		MyMath::Matrix4x4 viewMat = rc->MakeViewMatrix();
		glUniformMatrix4fv(uniforms[CONVERT(UNIFORM_TYPE::VIEW)], 1, GL_TRUE, viewMat.GetMatrix());
		break;
	}
	case UNIFORM_TYPE::PROJ:
	{
		MyMath::Matrix4x4 projMat = rc->MakeProjMatrix();
		glUniformMatrix4fv(uniforms[CONVERT(UNIFORM_TYPE::PROJ)], 1, GL_TRUE, projMat.GetMatrix());
		break;
	}
	case UNIFORM_TYPE::EYE:
	{
		MyMath::Vector3 eye = rc->GetEYE();
		GLfloat fEye[3] = { eye.x,eye.y,eye.z };
		glUniform3fv(uniforms[CONVERT(UNIFORM_TYPE::EYE)], 1, fEye);
		break;
	}
	}
}

void Renderer::UpdateTextures()
{
	glGenTextures(CONVERT(TEX_TYPE::NUM_TEX), Texs);
	glBindTexture(GL_TEXTURE_2D, Texs[CONVERT(TEX_TYPE::MAIN)]);

	TextureData *texData = renderContext.renderGO->GetTexture()->GetData();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texData->width, texData->height, 0, GL_BGR, GL_UNSIGNED_BYTE, texData->imageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, renderContext.texFilter.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, renderContext.texFilter.maxFilter);
}

void Renderer::DrawCall()
{
	if (drawCount > 0)
	{
		glDrawElements(renderContext.renderGO->GetMesh()->GetPrimitiveType(), drawCount, GL_UNSIGNED_INT, 0);
	}
}

Renderer::~Renderer()
{
	glDeleteBuffers(CONVERT(IBO_TYPE::NUM_IBO), IBOs);
	glDeleteBuffers(CONVERT(VBO_TYPE::NUM_VBO), VBOs);
	glDeleteVertexArrays(CONVERT(VAO_TYPE::NUM_VAO), VAOs);
}

///For Debug
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
