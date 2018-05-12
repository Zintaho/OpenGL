#include "MyMath.h"
using namespace MyMath;

Vector3 MyMath::CrossProduct(const Vector3 u, const Vector3 v)
{
	Vector3 result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;

	return result;
}