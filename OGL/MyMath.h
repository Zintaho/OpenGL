#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

///Cmath extension
namespace MyMath
{
	///Vector3
	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3 operator -(const Vector3 u) const
		{
			Vector3 tempVec;
			tempVec.x = x - u.x;
			tempVec.y = y - u.y;
			tempVec.z = z - u.z;

			return tempVec;
		}
	};
	///Vector4
	struct Vector4
	{
		float x;
		float y;
		float z;
		float w;

		Vector4 operator -(const Vector4 u) const
		{
			Vector4 tempVec;
			tempVec.x = x - u.x;
			tempVec.y = y - u.y;
			tempVec.z = z - u.z;

			return tempVec;
		}
	};

	///Matrix 4x4
	using Matrix4x4 = float[4][4];

	///Vertex
	struct Vertex
	{
		Vector3 Pos;
		Vector3 Color;
	};

	Vector3 CrossProduct(const Vector3 u, const Vector3 v);
	Vector3 ReturnUnitVec3(const Vector3 v);
	Vector3 MultiplyMatVec(const Matrix4x4 mat, const Vector3 v);

	void setViewMatrix(Matrix4x4 mat, const Vector3 EYE, const Vector3 AT, const Vector3 UP);
	void setProjMatrix(Matrix4x4 mat, const float fovy, const float aspect, const float n, const float f);

}

