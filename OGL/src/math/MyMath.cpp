#include "MyMath.h"
using namespace MyMath;

float MyMath::DotProduct(const Vector2 left, const Vector2 right)
{
	return left.u*right.u + left.v * right.v;
}
float MyMath::DotProduct(const Vector3 left, const Vector3 right)
{
	return left.x*right.x + left.y * right.y + left.z * right.z;
}
float MyMath::DotProduct(const Vector4 left, const Vector4 right)
{
	return left.x*right.x + left.y * right.y + left.z * right.z;
}

Vector3 MyMath::CrossProduct(const Vector3 u, const Vector3 v)
{
	Vector3 result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;

	return result;
}