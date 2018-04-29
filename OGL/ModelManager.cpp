#include "ModelManager.h"

std::vector<Vertex> ModelManager::vertice;

void ModelManager::ProcessObject(GameObject & gObj)
{
	using namespace std;

	const std::string modelPathHeader = ".\\model\\";
	const std::string modelPathFooter = ".obj";

	string path, buffer;
	ifstream sourceStream;
	///Load
	vertice.clear();
	path = modelPathHeader + gObj.GetFileName() + modelPathFooter;
	sourceStream.open(path);
	if (sourceStream)
	{
		while (not sourceStream.eof())
		{
			getline(sourceStream, buffer);
			if (buffer[0] == 'v')
			{
				//TODO
				
			}
		}
		sourceStream.close();
	}

}
