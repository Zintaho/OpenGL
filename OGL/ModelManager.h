#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <vector>

/*
1. GameObject 생성시 모델명 입력
2. Draw를 원할 경우 해당 GameObject를 드로우 큐에 넣음. //병렬 처리시 드로우 객체와 ModelManager간에 충돌 가능성에 주의
3. 드로우 큐에서 순번이 온 GameObject의 모델명을 획득함.
4. 모델명을 바탕으로 ModelManager의 메서드로 읽어서 Vertex 벡터에 저장 + 해당 GameObject의 position 등을 계산
5. 드로우 객체가 Vertex 벡터를 읽어 실제로 드로우
*/

class ModelManager
{
public:
	static void ProcessObject(GameObject &gObj);
	static std::vector<Vertex> vertice;
	static std::vector<int> indice;
};

