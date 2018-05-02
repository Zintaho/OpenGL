#pragma once
#include "MyMath.h"

class Transform
{
public:
	Transform(const MyMath::Vector3& trans, const MyMath::Vector3& rot, const MyMath::Vector3& scale = { 1.0f,1.0f,1.0f }) :
		translate(trans),rotate(rot),scale(scale) {};

	inline MyMath::Vector3 GetTrans(){ return translate; }
	inline MyMath::Vector3 GetRotate() { return rotate; }
	inline MyMath::Vector3 GetScale() { return scale; }

	inline void SetTrans(MyMath::Vector3 trans) { this->translate = trans; }
	inline void SetRotate(MyMath::Vector3 rotate) { this->rotate= rotate; }
	inline void SetScale(MyMath::Vector3 scale) { this->scale = scale; }
		
	virtual ~Transform();
private:
	MyMath::Vector3 translate;
	MyMath::Vector3 rotate;
	MyMath::Vector3 scale;
};

