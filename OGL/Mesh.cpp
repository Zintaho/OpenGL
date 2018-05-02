#include "Mesh.h"

Mesh::Mesh(Vertex * vertice, size_t numVertice)
{
	drawCount = numVertice;

	glGenVertexArrays(NUM_VAO, VAOs);
	glBindVertexArray(VAOs[0]);

	glGenBuffers(NUM_VBO, VBOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[static_cast<int>(VBO_TYPE::POS)]);
	glBufferData(GL_ARRAY_BUFFER, numVertice * sizeof(Vertex), vertice, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void Mesh::DrawMesh()
{
	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(drawCount));

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(NUM_VAO, VAOs);
}
