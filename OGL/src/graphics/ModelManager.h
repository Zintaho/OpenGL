#pragma once
#include "Mesh.h"

#include <fstream>
#include <sstream>
#include <vector>

/*
1. GameObject ������ �𵨸� �Է�
2. Draw�� ���� ��� �ش� GameObject�� ��ο� ť�� ����. //���� ó���� ��ο� ��ü�� ModelManager���� �浹 ���ɼ��� ����
3. ��ο� ť���� ������ �� GameObject�� �𵨸��� ȹ����.
4. �𵨸��� �������� ModelManager�� �޼���� �о Vertex ���Ϳ� ���� + �ش� GameObject�� position ���� ���
5. ��ο� ��ü�� Vertex ���͸� �о� ������ ��ο�
*/

class ModelManager
{
public:
	void LoadObj(Mesh *pMesh);

	MyMath::Vector3 centerPos;
private:
	std::vector<std::string> StringSpliter(std::string buffer, char token);
};

