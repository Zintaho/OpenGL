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
	Vector3 CrossProduct(const Vector3 u, const Vector3 v);
	Vector3 ReturnUnitVec3(const Vector3 v);

	///Matrix 4x4
	using Matrix4x4 = float[4][4];

	void setViewMatrix(Matrix4x4 mat, const Vector3 EYE, const Vector3 AT, const Vector3 UP);

}


