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

Vector3 MyMath::ReturnUnitVec3(const Vector3 v)
{
	Vector3 rVec = v;
	float norm = sqrt(v.x * v.x + v.y*v.y + v.z*v.z);

	rVec.x /= norm;
	rVec.y /= norm;
	rVec.z /= norm;

	return rVec;
}

void MyMath::setViewMatrix(Matrix4x4 mat, const Vector3 EYE, const Vector3 AT, const Vector3 UP)
{
	///Get u, v, n
	Vector3 u, v, n;
	n = EYE - AT;
	n = ReturnUnitVec3(n);

	u = CrossProduct(n, UP);
	u = ReturnUnitVec3(u);

	v = CrossProduct(n, u);
	///Set Matrix
	mat[0][0] = u.x;	mat[0][1] = u.y;	mat[0][2] = u.z;
	mat[0][3] = -EYE.x * (u.x + u.y + u.z);
	mat[1][0] = v.x;	mat[1][1] = v.y;	mat[1][2] = v.z;
	mat[1][3] = -EYE.y * (v.x + v.y + v.z);
	mat[2][0] = n.x;	mat[2][1] = n.y;	mat[2][2] = n.z;
	mat[2][3] = -EYE.z * (n.x + n.y + n.z);
	for (int z = 0; z < 3; ++z)
	{
		mat[3][z] = 0;
	}
	mat[3][3] = 1;
}
