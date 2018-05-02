#pragma once
#include "MyMath.h"
#include "RenderConstants.h"

#include <GL/glew.h>

///Vertex
struct Vertex
{
	MyMath::Vector3 Pos;
	//MyMath::Vector3 Normal;
	//MyMath::Vector2 TextureUV;
};

class Mesh
{
public:
	Mesh();
	Mesh(Vertex* vertice, size_t numVertice);
	virtual ~Mesh();

	void InitMesh(Vertex* vertice, size_t numVertice);
	void DrawMesh();
private:
	enum class VAO_TYPE : GLuint
	{
		MAIN = 0,

		NUM_VAO
	};
	enum class VBO_TYPE : GLuint
	{
		POS = 0,

		NUM_VBO
	};

	unsigned int VAOs[static_cast<GLuint>(VAO_TYPE::NUM_VAO)];
	unsigned int VBOs[static_cast<GLuint>(VBO_TYPE::NUM_VBO)];
	size_t drawCount;

	bool isMeshInitialized;
};