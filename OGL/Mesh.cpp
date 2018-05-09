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
	GLsizei vertexSize = static_cast<GLsizei>(sizeof(Vertex));

	glGenVertexArrays(VAOTYPE(VAO_TYPE::NUM_VAO), VAOs);
	glBindVertexArray(VAOs[VAOTYPE(VAO_TYPE::MAIN)]);

	glGenBuffers(VBOTYPE(VBO_TYPE::NUM_VBO), VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOTYPE(VBO_TYPE::POS)]);
	glBufferData(GL_ARRAY_BUFFER, numVertice * vertexSize, vertice, GL_STATIC_DRAW);

	glEnableVertexAttribArray(VBOTYPE(VBO_TYPE::POS));
	glVertexAttribPointer(VBOTYPE(VBO_TYPE::POS), 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
	glEnableVertexAttribArray(VBOTYPE(VBO_TYPE::NORMAL));
	glVertexAttribPointer(VBOTYPE(VBO_TYPE::NORMAL), 3, GL_FLOAT, GL_FALSE, vertexSize, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[VBOTYPE(VBO_TYPE::INDEX)]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndice * sizeof(unsigned int), indice, GL_STATIC_DRAW);
}

Mesh::Mesh(Vertex * vertice, GLsizei numVertice, unsigned int* indice, GLsizei numIndice)
{
	InitMesh(vertice, numVertice, indice, numIndice);
}

void Mesh::DrawMesh()
{
	if (drawCount > 0)
	{
		glBindVertexArray(VAOs[VAOTYPE(VAO_TYPE::MAIN)]);

		glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(NULL);
	}
}

void Mesh::CleanArray()
{
	glDeleteVertexArrays(VAOTYPE(VAO_TYPE::NUM_VAO), VAOs);
	glDeleteBuffers(VBOTYPE(VBO_TYPE::NUM_VBO), VBOs);
}

Mesh::~Mesh()
{
	if (isMeshInitialized)
	{
		CleanArray();
	}
}
