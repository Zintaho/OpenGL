#pragma once
#include "Mesh.h"

#include <fstream>
#include <sstream>
#include <vector>

class ModelManager
{
public:
	void LoadObj(Mesh *pMesh);
private:
	std::vector<std::string> StringSpliter(std::string buffer, char token);
};

