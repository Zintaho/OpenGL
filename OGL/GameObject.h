#pragma once
#include <string>
#include "MyMath.h"

class GameObject
{
public:
	GameObject(std::string fileName);
	~GameObject();

	std::string GetFileName();

	MyMath::Vector3 position;
private:
	MyMath::uInt32 drawPriority;
	std::string modelFileName;
};

