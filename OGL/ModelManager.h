#pragma once
#include "GameObject.h"
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
	static void ProcessObject(GameObject &gObj);
	static std::vector<Vertex> vertice;
	static std::vector<int> indice;
};

