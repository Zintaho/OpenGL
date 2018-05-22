#pragma once
#include "../../src/math/MyMath.h"

#include <vector>
#include <string>

///Vertex
struct Vertex
{
	MyMath::Vector3 Pos;
	//MyMath::Vector2 TextureUV;
	//MyMath::Vector3 Normal;
};
class Mesh
{
public:	
	Mesh(const char* fileName) :
		fileName(fileName) {};
	virtual ~Mesh()
	{
		ClearMesh();
	}

	inline void ClearMesh()
	{
		vertice.clear();
		indice.clear();
	}

	inline std::vector<Vertex> &GetVertice() { return vertice; }
	inline std::vector<unsigned int> &GetIndice() { return indice; }
	inline std::string GetFileName() const { return fileName; } 
private:
	std::vector<Vertex> vertice;
	std::vector<unsigned int> indice;
	std::string fileName;
};
