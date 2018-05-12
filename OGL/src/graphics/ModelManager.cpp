#include "ModelManager.h"

#include <iostream>

MyMath::Vector3	ModelManager::centerPos;
std::vector<Vertex> ModelManager::vertice;
std::vector<unsigned int> ModelManager::indice;
GLuint ModelManager::verticeNum;
GLuint ModelManager::indiceNum;

std::vector<std::string> StringSpliter(std::string buffer, char token)
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

void ModelManager::ProcessModel(std::string fileName)
{
	using namespace std;
	using namespace MyMath;

	struct ObjIndice
	{
		unsigned int pos = -1;
		unsigned int normal = -1;
		unsigned int uv = -1;
	};

	centerPos = { 0,0,0 };

	std::vector<MyMath::Vector3> positions;
	std::vector<MyMath::Vector3> normals;
	std::vector<MyMath::Vector2> uvs;
	std::vector<ObjIndice> objIndice;

	const std::string modelPathHeader = ".\\model\\";
	const std::string modelPathFooter = ".obj";

	string path, buffer;
	ifstream sourceStream;

	bool hasVN = false;
	bool hasVT = false;
	bool isVNVT = false;
	bool isVTVN = false;
	///Load
	vertice.clear();
	indice.clear();

	path = modelPathHeader + fileName + modelPathFooter;
	sourceStream.open(path);
	if (sourceStream)
	{
		while (not sourceStream.eof())
		{
			getline(sourceStream, buffer);

			vector<string> splitedBuffer = StringSpliter(buffer, ' ');

			if (splitedBuffer.size() > 0)
			{
				string lineHeader = splitedBuffer[0];
				if (lineHeader == "v")
				{
					Vector3 tempVec = { stof(splitedBuffer[1]),stof(splitedBuffer[2]),stof(splitedBuffer[3]) };
					positions.push_back(tempVec);
				}
				else if (lineHeader == "vt")
				{
					Vector2 tempVec = { stof(splitedBuffer[1]),stof(splitedBuffer[2]) };
					try
					{
						uvs.push_back(tempVec);
					}
					catch (...)
					{
						cout << uvs.size() << endl;
					}
				}
				else if (lineHeader == "vn")
				{
					Vector3 tempVec = { stof(splitedBuffer[1]),stof(splitedBuffer[2]),stof(splitedBuffer[3]) };
					normals.push_back(tempVec);
				}
				else if (lineHeader == "f")
				{
					//Vector3 tes;
				}
			}


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
	for (auto oi : objIndice)
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
}