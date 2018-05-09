#pragma once
#include <string>

#include "MyMath.h"
#include "Transform.h"
#include "Mesh.h"

class GameObject
{
public:
	GameObject(Mesh* pMesh, MyMath::Vector3 pos, MyMath::Vector3 rot, MyMath::Vector3 sc) :
		mesh(pMesh), transform(pos, rot, sc)
	{
		centerPos = { 0,0,0 };
	};
	~GameObject();
	inline Transform& GetTransform() { return transform; }
	inline Mesh* GetMesh() { return mesh; }

	MyMath::Vector3 centerPos;
private:
	Transform transform;
	Mesh *mesh;

	int drawPriority;
};

