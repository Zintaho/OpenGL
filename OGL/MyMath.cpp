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
	float norm = sqrtf(v.x * v.x + v.y*v.y + v.z*v.z);

	rVec.x /= norm;
	rVec.y /= norm;
	rVec.z /= norm;

	return rVec;
}

void MyMath::setTranslateMatrix(Matrix4x4 mat, const float X, const float Y, const float Z)
{

	mat[0][3] = X;
	mat[1][3] = Y;
	mat[2][3] = Z;
	mat[3][3] = 1;

	mat[0][0] = mat[1][1] = mat[2][2] = 1;
}

void MyMath::setScaleMatrix(Matrix4x4 mat, const float X, const float Y, const float Z)
{
	mat[0][0] = X;
	mat[1][1] = Y;
	mat[2][2] = Z;
	mat[3][3] = 1;
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

void MyMath::setProjMatrix(Matrix4x4 mat, const float fovy, const float aspect, const float n, const float f)
{
	float radFovy = fovy * (float)M_PI / 180.0f;
	
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			mat[y][x] = 0;
		}
	}

	mat[0][0] = -1 / (tan(radFovy / 2) *aspect);
	mat[1][1] = -1 / (tan(radFovy / 2));
	mat[2][2] = -((f + n) / (f - n));
	mat[2][3] = -2 * n*f / (f - n);
	mat[3][2] = -1;
}

Vector3 MyMath::MultiplyMatVec(const Matrix4x4 mat, const Vector3 v)
{
	Vector4 temp = { 0 };
	Vector4 homoV;
	
	homoV.x = v.x;
	homoV.y = v.y;
	homoV.z = v.z;
	homoV.w = 1;

	temp.w = 1;

	temp.x = (mat[0][0] * homoV.x + mat[0][1] * homoV.y + mat[0][2] * homoV.z + mat[0][3] * homoV.w);
	temp.y = (mat[1][0] * homoV.x + mat[1][1] * homoV.y + mat[1][2] * homoV.z + mat[1][3] * homoV.w);
	temp.z = (mat[2][0] * homoV.x + mat[2][1] * homoV.y + mat[2][2] * homoV.z + mat[2][3] * homoV.w);
	temp.w = (mat[3][0] * homoV.x + mat[3][1] * homoV.y + mat[3][2] * homoV.z + mat[3][3] * homoV.w);

	Vector3 rVec;
	rVec.x = temp.x;
	rVec.y = temp.y;
	rVec.z = temp.z;

	return rVec;
}

