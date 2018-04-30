#include "ModelManager.h"

std::vector<Vertex> ModelManager::vertice;
std::vector<int> ModelManager::indice;

void ModelManager::ProcessObject(GameObject & gObj)
{
	using namespace std;
	using namespace MyMath;

	const std::string modelPathHeader = ".\\model\\";
	const std::string modelPathFooter = ".obj";

	string path, buffer;
	ifstream sourceStream;
	Vector3 pos = { 0,0,0 };
	///Load
	vertice.clear();
	indice.clear();

	path = modelPathHeader + gObj.GetFileName() + modelPathFooter;
	sourceStream.open(path);
	if (sourceStream)
	{
		while (not sourceStream.eof())
		{
			getline(sourceStream, buffer);
			if (buffer[0] == 'v')
			{
				if (buffer[1] == ' ')
				{///VERTEX
					istringstream iss(buffer);
					string token;
					Vertex tempVertex;

					float tempXYZ[3];
					int index = 0;
					while (getline(iss, token, ' ') && index < 3)
					{
						if (token.size() > 0 && token[0] != 'v' && token[0] != ' ')
						{
							tempXYZ[index++] = stof(token);
						}
					}
					tempVertex.Pos.x = tempXYZ[0];
					tempVertex.Pos.y = tempXYZ[1];
					tempVertex.Pos.z = tempXYZ[2];
					pos.x += tempXYZ[0];
					pos.y += tempXYZ[1];
					pos.z += tempXYZ[2];
					vertice.push_back(tempVertex);
				}
			}
			else if (buffer[0] == 'f')
			{
				istringstream iss(&buffer[2]);
				string token;

				while (getline(iss, token, ' '))
				{
					istringstream tokenIss(token);
					string tokenToken;
					getline(tokenIss, tokenToken, '/');

					int i = abs(stoi(tokenToken)) - 1;
					indice.push_back(i);
				}
			}
		}
		sourceStream.close();
	}

	size_t verticeSize = vertice.size();
	pos.x /= verticeSize;
	pos.y /= verticeSize;
	pos.z /= verticeSize;

	gObj.position = pos;
}
