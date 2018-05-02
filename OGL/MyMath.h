#pragma once
#include <math.h>

///CMh extension
namespace MyMath
{
	///Vector2
	struct Vector2
	{
		float u;
		float v;

		Vector2 operator +(const Vector2 n) const
		{
			Vector2 tempVec;
			tempVec.u = u + n.u;
			tempVec.v = v + n.v;

			return tempVec;
		}

		Vector2 operator -(const Vector2 n) const
		{
			Vector2 tempVec;
			tempVec.u = u - n.u;
			tempVec.v = v - n.v;

			return tempVec;
		}
	};

	///Vector3
	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3 operator +(const Vector3 u) const
		{
			Vector3 tempVec;
			tempVec.x = x + u.x;
			tempVec.y = y + u.y;
			tempVec.z = z + u.z;

			return tempVec;
		}

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

		Vector4 operator +(const Vector4 u) const
		{
			Vector4 tempVec;
			tempVec.x = x + u.x;
			tempVec.y = y + u.y;
			tempVec.z = z + u.z;

			return tempVec;
		}

		Vector4 operator -(const Vector4 u) const
		{
			Vector4 tempVec;
			tempVec.x = x - u.x;
			tempVec.y = y - u.y;
			tempVec.z = z - u.z;

			return tempVec;
		}
	};
	Vector3 CrossProduct(const Vector3 u, const Vector3 v);
	Vector3 ReturnUnitVec3(const Vector3 v);

	///Matrix 4x4
	struct Matrix4x4
	{
		float M[4][4];

		void Clear()
		{
			for (int y = 0; y < 4; ++y)
			{
				for (int x = 0; x < 4; ++x)
				{
					M[y][x] = 0;
				}
			}
		}

		void SetTranslateMatrix(const float X, const float Y, const float Z)
		{
			Clear();

			M[0][3] = X;
			M[1][3] = Y;
			M[2][3] = Z;
			M[3][3] = 1;

			M[0][0] = M[1][1] = M[2][2] = 1;
		}

		void SetScaleMatrix(const float X, const float Y, const float Z)
		{
			Clear();

			M[0][0] = X;
			M[1][1] = Y;
			M[2][2] = Z;
			M[3][3] = 1;
		}

		void SetViewMatrix(const Vector3 EYE, const Vector3 AT, const Vector3 UP)
		{
			Clear();

			///Get u, v, n
			Vector3 u, v, n;
			n = EYE - AT;
			n = ReturnUnitVec3(n);

			u = CrossProduct(n, UP);
			u = ReturnUnitVec3(u);

			v = CrossProduct(n, u);
			///Set Matrix
			M[0][0] = u.x;	M[0][1] = u.y;	M[0][2] = u.z;
			M[0][3] = -EYE.x * (u.x + u.y + u.z);
			M[1][0] = v.x;	M[1][1] = v.y;	M[1][2] = v.z;
			M[1][3] = -EYE.y * (v.x + v.y + v.z);
			M[2][0] = n.x;	M[2][1] = n.y;	M[2][2] = n.z;
			M[2][3] = -EYE.z * (n.x + n.y + n.z);
			for (int z = 0; z < 3; ++z)
			{
				M[3][z] = 0;
			}
			M[3][3] = 1;
		}

		void SetProjMatrix(const float fovy, const float aspect, const float n, const float f)
		{
			Clear();

			float radFovy = fovy * (float)3.141592f / 180.0f;

			for (int y = 0; y < 4; ++y)
			{
				for (int x = 0; x < 4; ++x)
				{
					M[y][x] = 0;
				}
			}

			M[0][0] = -1 / (tanf(radFovy / 2) *aspect);
			M[1][1] = -1 / (tanf(radFovy / 2));
			M[2][2] = -((f + n) / (f - n));
			M[2][3] = -2 * n*f / (f - n);
			M[3][2] = -1;
		}

		Matrix4x4 operator* (const Matrix4x4 MB)
		{
			Matrix4x4 MA;
			for (int y = 0; y < 4; ++y)
			{
				for (int x = 0; x < 4; ++x)
				{
					MA.M[y][x] = 0;
					for (int j = 0; j < 4; ++j)
					{
						MA.M[y][x] += M[y][j] * MB.M[j][x];
					}
				}
			}
			return MA;
		}

		Vector3 operator* (const Vector3 vec)
		{
			Vector4 tempVec4 = { vec.x, vec.y, vec.z, 1 };

			tempVec4.x = (M[0][0] * tempVec4.x + M[0][1] * tempVec4.y + M[0][2] * tempVec4.z + M[0][3] * tempVec4.w);
			tempVec4.y = (M[1][0] * tempVec4.x + M[1][1] * tempVec4.y + M[1][2] * tempVec4.z + M[1][3] * tempVec4.w);
			tempVec4.z = (M[2][0] * tempVec4.x + M[2][1] * tempVec4.y + M[2][2] * tempVec4.z + M[2][3] * tempVec4.w);
			tempVec4.w = (M[3][0] * tempVec4.x + M[3][1] * tempVec4.y + M[3][2] * tempVec4.z + M[3][3] * tempVec4.w);

			Vector3 tempVec3 = { tempVec4.x, tempVec4.y, tempVec4.z };

			return tempVec3;
		}
	};
}

