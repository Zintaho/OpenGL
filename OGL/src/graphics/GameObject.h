#pragma once
#include <string>

#include "../../src/math/MyMath.h"
#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"

class GameObject
{
public:
	GameObject()
	{
		mesh = 0;
	}
	GameObject(Mesh* pMesh, Transform tr) :
		mesh(pMesh), transform(tr)
	{};
	virtual ~GameObject();
	inline Transform& GetTransform() { return transform; }
	inline Mesh* GetMesh() { return mesh; }
	inline Texture* GetTexture() { return texture; };
	inline void SetTexture(Texture *tx) { this->texture = tx; }
private:
	Transform transform;
	Mesh *mesh;
	Texture *texture;

	int drawPriority;
};

