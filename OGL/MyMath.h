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
	class Matrix4x4
	{
	public:
		Matrix4x4()
		{
			Clear();
		}
		inline float* GetMatrix()
		{
			return this->mat.M;
		}
		inline void Clear()
		{
			for (int y = 0; y < 4; ++y)
			{
				for (int x = 0; x < 4; ++x)
				{
					this->mat(y, x) = 0;
				}
			}
		}
		inline void SetTranslateMatrix(const float X, const float Y, const float Z)
		{
			mat(0,3) = X;
			mat(1,3) = Y;
			mat(2,3) = Z;
			mat(3,3) = 1;

			mat(0,0) = mat(1,1) = mat(2,2) = 1;
		}
		inline void SetScaleMatrix(const float X, const float Y, const float Z)
		{
			mat(0,0) = X;
			mat(1,1) = Y;
			mat(2,2) = Z;
			mat(3,3) = 1;
		}
		inline void SetViewMatrix(const Vector3 EYE, const Vector3 AT, const Vector3 UP)
		{
			///Get u, v, n
			Vector3 u, v, n;
			n = EYE - AT;
			n = ReturnUnitVec3(n);

			u = CrossProduct(n, UP);
			u = ReturnUnitVec3(u);

			v = CrossProduct(n, u);
			///Set Matrix
			mat(0,0) = u.x;	mat(0,1) = u.y;	mat(0,2) = u.z;
			mat(0,3) = -EYE.x * (u.x + u.y + u.z);
			mat(1,0) = v.x;	mat(1,1) = v.y;	mat(1,2) = v.z;
			mat(1,3) = -EYE.y * (v.x + v.y + v.z);
			mat(2,0) = n.x;	mat(2,1) = n.y;	mat(2,2) = n.z;
			mat(2,3) = -EYE.z * (n.x + n.y + n.z);
			for (int z = 0; z < 3; ++z)
			{
				mat(3,z) = 0;
			}
			mat(3,3) = 1;
		}
		inline void SetProjMatrix(const float fovy, const float aspect, const float n, const float f)
		{
			const float PI = 3.14159265f;
			float radFovy = fovy * PI / 180.0f;

			mat(0,0) = -1 / (tanf(radFovy / 2) *aspect);
			mat(1,1) = -1 / (tanf(radFovy / 2));
			mat(2,2) = -((f + n) / (f - n));
			mat(2,3) = -2 * n*f / (f - n);
			mat(3,2) = -1;
		}

		Matrix4x4 operator* (Matrix4x4 MB)
		{
			Matrix4x4 MA;
			for (int y = 0; y < 4; ++y)
			{
				for (int x = 0; x < 4; ++x)
				{
					for (int j = 0; j < 4; ++j)
					{
						MA.mat(y, x) += (mat(y, j) * MB.mat(j, x));
					}
				}
			}
			return MA;
		}

		Vector3 operator* (const Vector3 vec)
		{
			Vector4 tempVec4 = { vec.x, vec.y, vec.z, 1 };

			tempVec4.x = (mat(0,0) * tempVec4.x + mat(0,1) * tempVec4.y + mat(0,2) * tempVec4.z + mat(0,3) * tempVec4.w);
			tempVec4.y = (mat(1,0) * tempVec4.x + mat(1,1) * tempVec4.y + mat(1,2) * tempVec4.z + mat(1,3) * tempVec4.w);
			tempVec4.z = (mat(2,0) * tempVec4.x + mat(2,1) * tempVec4.y + mat(2,2) * tempVec4.z + mat(2,3) * tempVec4.w);
			tempVec4.w = (mat(3,0) * tempVec4.x + mat(3,1) * tempVec4.y + mat(3,2) * tempVec4.z + mat(3,3) * tempVec4.w);

			Vector3 tempVec3 = { tempVec4.x, tempVec4.y, tempVec4.z };

			return tempVec3;
		}

	private:
		struct Matrix
		{
			float M[4 * 4];

			float& operator()(int y, int x)
			{
				return M[y * 4 + x];
			}
		};

		Matrix mat;
	};
}

