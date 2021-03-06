#pragma once
#include "../../src/math/MyMath.h"

class Transform
{
public:
	Transform()
	{
		position = MyMath::Vector3(0, 0, 0);
		rotation = MyMath::Vector3(0, 0, 0);
		scale = MyMath::Vector3(1, 1, 1);
	}
	Transform(const MyMath::Vector3& pos, const MyMath::Vector3& rot, const MyMath::Vector3& scale = { 1.0f,1.0f,1.0f }) :
		position(pos), rotation(rot), scale(scale) {};

	inline MyMath::Matrix4x4 MakeMatrix()
	{
		MyMath::Matrix4x4 transMat;
		transMat.SetTranslateMatrix(position.x, position.y, position.z);
		MyMath::Matrix4x4 scaleMat;
		scaleMat.SetScaleMatrix(scale.x, scale.y, scale.z);
		MyMath::Matrix4x4 rotateXMat;
		rotateXMat.SetRotXMatrix(rotation.x);
		MyMath::Matrix4x4 rotateYMat;
		rotateYMat.SetRotYMatrix(rotation.y);
		MyMath::Matrix4x4 rotateZMat;
		rotateZMat.SetRotZMatrix(rotation.z);

		MyMath::Matrix4x4 returnMat = transMat * rotateZMat * rotateXMat * rotateYMat *  scaleMat;

		return returnMat;
	}

	inline MyMath::Vector3& GetTrans(){ return position; }
	inline MyMath::Vector3& GetRotate() { return rotation; }
	inline MyMath::Vector3& GetScale() { return scale; }

	inline void SetTrans(MyMath::Vector3 trans) { this->position = trans; }
	inline void SetRotate(MyMath::Vector3 rotate) { this->rotation= rotate; }
	inline void SetScale(MyMath::Vector3 scale) { this->scale = scale; }
		
	virtual ~Transform();
private:
	MyMath::Vector3 position;
	MyMath::Vector3 rotation;
	MyMath::Vector3 scale;
};

