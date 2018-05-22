#pragma once
#include <string>

#include "../../src/math/MyMath.h"
#include "Transform.h"
#include "Mesh.h"

class GameObject
{
public:
	GameObject(Mesh* pMesh, Transform tr) :
		mesh(pMesh), transform(tr)
	{};
	virtual ~GameObject();
	inline Transform& GetTransform() { return transform; }
	inline Mesh* GetMesh() { return mesh; }
private:
	Transform transform;
	Mesh *mesh;

	int drawPriority;
};

