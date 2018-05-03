#include "Mesh.h"

Mesh::Mesh()
{
	drawCount = 0;
	isMeshInitialized = false;
}

void Mesh::InitMesh(Vertex * vertice, GLsizei numVertice, unsigned int* indice, GLsizei numIndice)
{
	isMeshInitialized = true;

	drawCount = numIndice;

	glGenVertexArrays(static_cast<GLuint>(VAO_TYPE::NUM_VAO), VAOs);
	glBindVertexArray(VAOs[static_cast<GLuint>(VAO_TYPE::MAIN)]);

	GLsizei vertexSize = static_cast<GLsizei>(sizeof(Vertex));

	glGenBuffers(static_cast<GLuint>(VBO_TYPE::NUM_VBO), VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[static_cast<GLuint>(VBO_TYPE::POS)]);
	glBufferData(GL_ARRAY_BUFFER, numVertice * vertexSize, vertice, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[static_cast<GLuint>(VBO_TYPE::INDEX)]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndice * sizeof(unsigned int), indice, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::Mesh(Vertex * vertice, GLsizei numVertice, unsigned int* indice, GLsizei numIndice)
{
	InitMesh(vertice, numVertice, indice, numIndice);
}

void Mesh::DrawMesh()
{
	if (drawCount > 0)
	{
		glBindVertexArray(VAOs[static_cast<GLuint>(VAO_TYPE::MAIN)]);

		glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);

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
