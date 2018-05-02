#include "Mesh.h"

Mesh::Mesh()
{
	drawCount = 0;
	isMeshInitialized = false;
}

void Mesh::InitMesh(Vertex * vertice, size_t numVertice)
{
	isMeshInitialized = true;

	drawCount = numVertice;

	glGenVertexArrays(static_cast<GLuint>(VAO_TYPE::NUM_VAO), VAOs);
	glBindVertexArray(VAOs[static_cast<GLuint>(VAO_TYPE::MAIN)]);

	glGenBuffers(static_cast<GLuint>(VBO_TYPE::NUM_VBO), VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[static_cast<GLuint>(VBO_TYPE::POS)]);
	glBufferData(GL_ARRAY_BUFFER, numVertice * sizeof(Vertex), vertice, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::Mesh(Vertex * vertice, size_t numVertice)
{
	InitMesh(vertice, numVertice);
}

void Mesh::DrawMesh()
{
	if (drawCount > 0)
	{
		glBindVertexArray(VAOs[static_cast<GLuint>(VAO_TYPE::MAIN)]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(drawCount));

		glBindVertexArray(0);
	}
}
Mesh::~Mesh()
{
	if (isMeshInitialized)
	{
		glDeleteVertexArrays(static_cast<GLuint>(VAO_TYPE::NUM_VAO), VAOs);
	}
}
