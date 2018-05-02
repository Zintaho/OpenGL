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
	Mesh(Vertex* vertice, size_t numVertice);

	void DrawMesh();

	virtual ~Mesh();
private:
	enum class VBO_TYPE
	{
		POS = 0
	};

	unsigned int VAOs[NUM_VAO];
	unsigned int VBOs[NUM_VBO];
	size_t drawCount;
};

