#pragma once
#include <string>

#include "MyMath.h"
#include "Transform.h"
#include "Mesh.h"

class GameObject
{
public:
	GameObject(std::string fileName, MyMath::Vector3 pos, MyMath::Vector3 rot, MyMath::Vector3 sc) :
		modelFileName(fileName), transform(pos, rot, sc)
	{
		centerPos = { 0,0,0 };
	};
	~GameObject();
	inline std::string& GetFileName() { return modelFileName; }
	inline Transform& GetTransform() { return transform; }
	inline Mesh& GetMesh() { return mesh; }

	MyMath::Vector3 centerPos;
private:
	std::string modelFileName;
	Transform transform;
	Mesh mesh;

	int drawPriority;
};

