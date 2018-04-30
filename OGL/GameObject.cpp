#include "GameObject.h"

GameObject::GameObject(std::string fileName)
{
	position = { 0,0,0 };
	modelFileName = fileName;
}

GameObject::~GameObject()
{
}

std::string GameObject::GetFileName()
{
	return modelFileName;
}