#pragma once
#include "MyMath.h"
#include "RenderConstants.h"

#include <GL/glew.h>

///Vertex
struct Vertex
{
	MyMath::Vector3 Pos;
	MyMath::Vector3 Normal;
	//MyMath::Vector2 TextureUV;
};

class Mesh
{
public:
	Mesh();
	Mesh(Vertex * vertice, GLsizei numVertice, unsigned int* indice, GLsizei numIndice);
	virtual ~Mesh();

	void InitMesh(Vertex * vertice, GLsizei numVertice, unsigned int* indice, GLsizei numIndice);
	void DrawMesh();
	void CleanArray();
private:
	enum class VAO_TYPE : GLuint
	{
		MAIN = 0,

		NUM_VAO
	};
	enum class VBO_TYPE : GLuint
	{
		POS = 0,
		NORMAL,
		INDEX,

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

	unsigned int VAOs[static_cast<GLuint>(VAO_TYPE::NUM_VAO)];
	unsigned int VBOs[static_cast<GLuint>(VBO_TYPE::NUM_VBO)];
	GLsizei drawCount;

	bool isMeshInitialized;
};