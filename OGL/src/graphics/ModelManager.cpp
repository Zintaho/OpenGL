#include "ModelManager.h"

#include <iostream>

void ModelManager::LoadObj(Mesh *pMesh)
{
	struct VertexIndex
	{
		unsigned int pos;
		unsigned int normal;
		unsigned int uv;
	};

	MyMath::Vector3 centerPos(0, 0, 0);

	std::vector<MyMath::Vector3> positions;
	std::vector<MyMath::Vector3> normals;
	std::vector<MyMath::Vector2> uvs;
	std::vector<VertexIndex> vertexIndice;

	const std::string modelPathHeader = ".\\model\\";
	const std::string modelPathFooter = ".obj";

	std::string path, buffer;
	std::ifstream sourceStream;

	///Clear mesh
	pMesh->GetVertice().clear();
	pMesh->GetIndice().clear();

	///Make & Open FilePath
	path = modelPathHeader + pMesh->GetFileName() + modelPathFooter;
	sourceStream.open(path);
	if (sourceStream)
	{
		while (not sourceStream.eof())
		{
			getline(sourceStream, buffer);

			std::vector<std::string> splitedBuffer = StringSpliter(buffer, ' ');

			if (splitedBuffer.size() > 0)
			{
				std::string lineHeader = splitedBuffer[0];
				if (lineHeader == "v")
				{
					MyMath::Vector3 tempVec(std::stof(splitedBuffer[1]), stof(splitedBuffer[2]), stof(splitedBuffer[3]));
					centerPos += tempVec;

					positions.push_back(tempVec);
				}
				else if (lineHeader == "vt")
				{
					MyMath::Vector2 tempVec(stof(splitedBuffer[1]), stof(splitedBuffer[2]));
					uvs.push_back(tempVec);

				}
				else if (lineHeader == "vn")
				{
					MyMath::Vector3 tempVec(stof(splitedBuffer[1]), stof(splitedBuffer[2]), stof(splitedBuffer[3]));
					normals.push_back(tempVec);
				}
				else if (lineHeader == "f")
				{///Only for v/vt/vn model
					for (int i = 1; i <= 3; ++i)
					{
						std::vector<std::string> splitedSplitedBuffer = StringSpliter(splitedBuffer[i], '/');
						VertexIndex tempVI;
						tempVI.pos = std::stoi(splitedSplitedBuffer[0]);
						tempVI.uv = std::stoi(splitedSplitedBuffer[1]);
						tempVI.normal = std::stoi(splitedSplitedBuffer[2]);

						vertexIndice.push_back(tempVI);
					}
				}

			}
		}
		///Calculate Center Position of GameObject
		size_t posCount = positions.size();
		centerPos.x /= posCount;
		centerPos.y /= posCount;
		centerPos.z /= posCount;

		///Translate Model
		for (auto pos : positions)
		{
			pos - centerPos;
		}

		Vertex tempVertex;
		VertexIndex tempVI;
		size_t vertexSize = vertexIndice.size();
		for (int i = 0; i < vertexSize; ++i)
		{
			tempVI = vertexIndice[i];
			tempVertex.Pos = positions[tempVI.pos - 1];
			tempVertex.Normal = normals[tempVI.normal - 1];
			tempVertex.TextureUV = uvs[tempVI.uv - 1];

			pMesh->GetVertice().push_back(tempVertex);
			pMesh->GetIndice().push_back(tempVI.uv - 1);
		}
	}
}

std::vector<std::string> ModelManager::StringSpliter(std::string buffer, char token)
{
	std::vector<std::string> splitedBuffer;
	std::string tempString = "";

	for (auto c : buffer)
	{
		if (c != token)
		{
			tempString += c;
		}
		else if (c == token && tempString != "")
		{
			splitedBuffer.push_back(tempString);
			tempString = "";
		}
	}
	if (tempString != "")
	{
		splitedBuffer.push_back(tempString);
	}

	return splitedBuffer;
}