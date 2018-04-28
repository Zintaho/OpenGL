#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

///Cmath extension
namespace MyMath
{
	struct Vector3
	{
		float x;
		float y;
		float z;
	};

	Vector3 CrossProduct(const Vector3 u, const Vector3 v);
}


