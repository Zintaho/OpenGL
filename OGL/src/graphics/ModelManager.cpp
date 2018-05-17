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

	centerPos = { 0,0,0 };

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
		std::cout << "TEST" << std::endl;

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
#if 0
		//	


		//	if (buffer[0] == 'v')
		//	{
		//		if (buffer[1] == ' ' || buffer[1] == '\t')
		//		{///VERTEX POSITION 
		//			istringstream iss(buffer);
		//			string token;

		//			Vector3 tempVec;
		//			float tempXYZ[3];
		//			int index = 0;
		//			while (getline(iss, token, ' ') && index < 3)
		//			{
		//				if (token.size() > 0 && token[0] != 'v' && token[0] != ' ')
		//				{
		//					tempXYZ[index++] = stof(token);
		//				}
		//			}

		//			tempVec = { tempXYZ[0], tempXYZ[1], tempXYZ[2] };
		//			centerPos = centerPos + tempVec;

		//			positions.push_back(tempVec);
		//		}
		//		else if (buffer[1] == 'n')
		//		{///VERTEX NORMAL
		//			hasVN = true;
		//			if (not isVNVT && not isVTVN)
		//			{
		//				isVNVT = true;
		//			}

		//			istringstream iss(buffer);
		//			string token;

		//			Vector3 tempVec;
		//			float tempXYZ[3];
		//			int index = 0;
		//			while (getline(iss, token, ' ') && index < 3)
		//			{
		//				if (token.size() > 0 && token[0] != 'v' && token[0] != ' ')
		//				{
		//					tempXYZ[index++] = stof(token);
		//				}
		//			}

		//			tempVec = { tempXYZ[0], tempXYZ[1], tempXYZ[2] };

		//			normals.push_back(tempVec);
		//		}
		//		else if (buffer[1] == 't')
		//		{///VERTEX TEXTURE UV
		//			hasVT = true;
		//			if (not isVNVT && not isVTVN)
		//			{
		//				isVTVN = true;
		//			}

		//			istringstream iss(buffer);
		//			string token;

		//			Vector2 tempVec;
		//			float tempXY[2];
		//			int index = 0;
		//			while (getline(iss, token, ' ') && index < 2)
		//			{
		//				if (token.size() > 0 && token[0] != 'v' && token[0] != ' ')
		//				{
		//					tempXY[index++] = stof(token);
		//				}
		//			}

		//			tempVec = { tempXY[0], tempXY[1] };

		//			uvs.push_back(tempVec);
		//		}
		//	}
		//	else if (buffer[0] == 'f')
		//	{
		//		istringstream iss(&buffer[2]);
		//		string token;

		//		while (getline(iss, token, ' '))
		//		{
		//			istringstream tokenIss(token);
		//			string tokenToken;
		//			ObjIndice oi;

		//			int index = 0;
		//			while (getline(tokenIss, tokenToken, '/') && index < 3)
		//			{
		//				if (tokenToken == "\0")
		//				{
		//					break;
		//				}
		//				else
		//				{///Please set v vt vn
		//					int i = abs(stoi(tokenToken)) - 1;
		//					if (index == 0)
		//					{
		//						oi.pos = i;
		//						indice.push_back(i);
		//					}
		//					else if (index == 1)
		//					{
		//						if (hasVT)
		//						{///vn only or vt only
		//							oi.uv = i;
		//						}
		//						else if (not hasVT)
		//						{
		//							oi.normal = i;
		//						}

		//					}
		//					else if (index == 2)
		//					{
		//						oi.normal = i;
		//					}

		//					++index;
		//				}
		//			}

		//			objIndice.push_back(oi);
		//		}
		//	}
	}
	sourceStream.close();
}

///Set Vertex
for (Vector3 v : positions)
{
	Vertex vv;
	vv.Pos = v;
	vv.Normal = { 0,0,0 };
	vertice.push_back(vv);
}

///Calculate Vertex Normal
for (auto oi : vertexIndice)
{
	vertice[oi.pos].Normal = vertice[oi.pos].Normal + normals[oi.normal];
}


///Calculate Center Position of GameObject
size_t verticeSize = vertice.size();
centerPos.x /= verticeSize;
centerPos.y /= verticeSize;
centerPos.z /= verticeSize;

verticeNum = static_cast<GLuint>(vertice.size());
indiceNum = static_cast<GLuint>(indice.size());
#endif
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