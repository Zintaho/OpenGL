#pragma once
#include <math.h>
#include <iostream>
#include <cassert>

///CMh extension
namespace MyMath
{
	const float PI = 3.141592f;
	constexpr void DivideByZeroAssert(float f)
	{
		assert(f != 0);
	}

	///Vector2
	struct Vector2
	{
		float u, v;

		Vector2()
		{
			u = v = 0.0f;
		}
		Vector2(float u, float v)
		{
			this->u = u;
			this->v = v;
		}

		friend Vector2 operator +(const Vector2& left, const Vector2& right)
		{
			Vector2 tempVec;
			tempVec.u = left.u + right.u;
			tempVec.v = left.v + right.v;

			return tempVec;
		}

		void operator +=(const Vector2& right)
		{
			this->u = this->u + right.u;
			this->v = this->v + right.v;
		}

		friend Vector2 operator -(const Vector2& left, const Vector2& right)
		{
			Vector2 tempVec;
			tempVec.u = left.u - right.u;
			tempVec.v = left.v - right.v;

			return tempVec;
		}

		void operator -=(const Vector2& right)
		{
			this->u = this->u - right.u;
			this->v = this->v - right.v;
		}

		friend Vector2 operator *(const Vector2& vec, const float& f)
		{
			Vector2 tempVec;
			tempVec.u = vec.u * f;
			tempVec.v = vec.v * f;

			return tempVec;
		}

		friend Vector2 operator *(const float& f, const Vector2& vec)
		{
			Vector2 tempVec;
			tempVec.u = vec.u * f;
			tempVec.v = vec.v * f;

			return tempVec;
		}

		void operator *=(const float& f)
		{
			this->u = this->u * f;
			this->v = this->v * f;
		}


		friend Vector2 operator /(const Vector2& vec, const float& f)
		{
			DivideByZeroAssert(f);

			Vector2 tempVec;
			tempVec.u = vec.u / f;
			tempVec.v = vec.v / f;

			return tempVec;
		}

		friend Vector2 operator /(const float& f, const Vector2& vec)
		{
			DivideByZeroAssert(f);

			Vector2 tempVec;
			tempVec.u = vec.u / f;
			tempVec.v = vec.v / f;

			return tempVec;
		}

		void operator /=(const float& f)
		{
			DivideByZeroAssert(f);

			this->u = this->u / f;
			this->v = this->v / f;
		}

		friend bool operator ==(const Vector2 &left, const Vector2 &right)
		{
			return left.u == right.u && left.v == right.v;
		}

		friend std::ostream& operator << (std::ostream& stream, const Vector2 &vec)
		{
			stream << '<' << vec.u << ',' << vec.v << '>';
			return stream;
		}

		Vector2 ConvertToUnitVector()
		{
			float norm = sqrtf(this->u*this->u + this->v * this->v);

			this->u /= norm;
			this->v /= norm;

			return *this;
		}

	};
	float DotProduct(const Vector2 left, const Vector2 right);


	///Vector3
	struct Vector3
	{
		float x, y, z;

		Vector3()
		{
			x = y = z =  0.0f;
		}
		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		friend Vector3 operator +(const Vector3& left, const Vector3& right)
		{
			Vector3 tempVec;
			tempVec.x = left.x + right.x;
			tempVec.y = left.y + right.y;
			tempVec.z = left.z + right.z;

			return tempVec;
		}

		void operator +=(const Vector3& right)
		{
			this->x = this->x + right.x;
			this->y = this->y + right.y;
			this->z = this->z + right.z;
		}

		friend Vector3 operator -(const Vector3& left, const Vector3& right)
		{
			Vector3 tempVec;
			tempVec.x = left.x - right.x;
			tempVec.y = left.y - right.y;
			tempVec.z = left.z - right.z;

			return tempVec;
		}

		void operator -=(const Vector3& right)
		{
			this->x = this->x - right.x;
			this->y = this->y - right.y;
			this->z = this->z - right.z;
		}

		friend Vector3 operator *(const Vector3& vec, const float& f)
		{
			Vector3 tempVec;
			tempVec.x = vec.x * f;
			tempVec.y = vec.y * f;
			tempVec.z = vec.z * f;

			return tempVec;
		}

		friend Vector3 operator *(const float& f, const Vector3& vec)
		{
			Vector3 tempVec;
			tempVec.x = vec.x * f;
			tempVec.y = vec.y * f;
			tempVec.z = vec.z * f;

			return tempVec;
		}

		void operator *=(const float& f)
		{
			this->x = this->x * f;
			this->y = this->y * f;
			this->z = this->z * f;
		}


		friend Vector3 operator /(const Vector3& vec, const float& f)
		{
			DivideByZeroAssert(f);

			Vector3 tempVec;
			tempVec.x = vec.x / f;
			tempVec.y = vec.y / f;
			tempVec.z = vec.z / f;

			return tempVec;
		}

		friend Vector3 operator /(const float& f, const Vector3& vec)
		{
			DivideByZeroAssert(f);

			Vector3 tempVec;
			tempVec.x = vec.x / f;
			tempVec.y = vec.y / f;
			tempVec.z = vec.z / f;

			return tempVec;
		}

		void operator /=(const float& f)
		{
			DivideByZeroAssert(f);

			this->x = this->x / f;
			this->y = this->y / f;
			this->z = this->z / f;
		}

		friend bool operator ==(const Vector3 &left, const Vector3 &right)
		{
			return left.x == right.x && left.y == right.y && left.z == right.z;
		}

		friend std::ostream& operator << (std::ostream& stream, const Vector3 &vec)
		{
			stream << '<' << vec.x << ',' << vec.y << ',' << vec.z <<'>';
			return stream;
		}

		Vector3 ConvertToUnitVector()
		{
			float norm = sqrtf(this->x*this->x + this->y * this->y + this->z * this->z);

			this->x /= norm;
			this->y /= norm;
			this->z /= norm;

			return *this;
		}

	};
	float DotProduct(const Vector3 left, const Vector3 right);
	Vector3 CrossProduct(const Vector3 u, const Vector3 v);


	///Vector4
	struct Vector4
	{
		float x, y, z, w;

		Vector4()
		{
			x = y = z = 0.0f;
			w = 1.0f;
		}
		Vector4(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			w = 1.0f;
		}		

		friend Vector4 operator +(const Vector4& left, const Vector4& right)
		{
			Vector4 tempVec;
			tempVec.x = left.x + right.x;
			tempVec.y = left.y + right.y;
			tempVec.z = left.z + right.z;

			return tempVec;
		}

		void operator +=(const Vector4& right)
		{
			this->x = this->x + right.x;
			this->y = this->y + right.y;
			this->z = this->z + right.z;
		}

		friend Vector4 operator -(const Vector4& left, const Vector4& right)
		{
			Vector4 tempVec;
			tempVec.x = left.x - right.x;
			tempVec.y = left.y - right.y;
			tempVec.z = left.z - right.z;

			return tempVec;
		}

		void operator -=(const Vector4& right)
		{
			this->x = this->x - right.x;
			this->y = this->y - right.y;
			this->z = this->z - right.z;
		}

		friend Vector4 operator *(const Vector4& vec, const float& f)
		{
			Vector4 tempVec;
			tempVec.x = vec.x * f;
			tempVec.y = vec.y * f;
			tempVec.z = vec.z * f;

			return tempVec;
		}

		friend Vector4 operator *(const float& f, const Vector4& vec)
		{
			Vector4 tempVec;
			tempVec.x = vec.x * f;
			tempVec.y = vec.y * f;
			tempVec.z = vec.z * f;

			return tempVec;
		}

		void operator *=(const float& f)
		{
			this->x = this->x * f;
			this->y = this->y * f;
			this->z = this->z * f;
		}


		friend Vector4 operator /(const Vector4& vec, const float& f)
		{
			DivideByZeroAssert(f);

			Vector4 tempVec;
			tempVec.x = vec.x / f;
			tempVec.y = vec.y / f;
			tempVec.z = vec.z / f;

			return tempVec;
		}

		friend Vector4 operator /(const float& f, const Vector4& vec)
		{
			DivideByZeroAssert(f);

			Vector4 tempVec;
			tempVec.x = vec.x / f;
			tempVec.y = vec.y / f;
			tempVec.z = vec.z / f;

			return tempVec;
		}

		void operator /=(const float& f)
		{
			DivideByZeroAssert(f);

			this->x = this->x / f;
			this->y = this->y / f;
			this->z = this->z / f;
		}

		friend bool operator ==(const Vector4 &left, const Vector4 &right)
		{
			return left.x == right.x && left.y == right.y && left.z == right.z;
		}

		friend std::ostream& operator << (std::ostream& stream, const Vector4 &vec)
		{
			stream << '<' << vec.x << ',' << vec.y << ',' << vec.z << ',' << vec.w << '>';
			return stream;
		}

		Vector4 ConvertToUnitVector()
		{
			float norm = sqrtf(this->x*this->x + this->y * this->y + this->z * this->z);

			this->x /= norm;
			this->y /= norm;
			this->z /= norm;

			return *this;
		}

	};
	float DotProduct(const Vector4 left, const Vector4 right);

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
		inline void SetIdentityMatrix()
		{
			mat(0, 0) = mat(1, 1) = mat(2, 2) = mat(3, 3) = 1;
		}

		inline void SetTranslateMatrix(const float X, const float Y, const float Z)
		{
			mat(3,0) = X;
			mat(3,1) = Y;
			mat(3,2) = Z;
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
		inline void SetRotXMatrix(const float radAngle)
		{
			mat(0, 0) = 1;
			mat(1, 1) = cosf(radAngle);
			mat(1, 2) = -sinf(radAngle);
			mat(2, 1) = sinf(radAngle);
			mat(2, 2) = cosf(radAngle);
			mat(3, 3) = 1;
		}
		inline void SetRotYMatrix(const float radAngle)
		{
			mat(0, 0) = cosf(radAngle);
			mat(0, 2) = sinf(radAngle);
			mat(1, 1) = 1;
			mat(2, 0) = -sinf(radAngle);
			mat(2, 2) = cosf(radAngle);
			mat(3, 3) = 1;
		}
		inline void SetRotZMatrix(const float radAngle)
		{
			mat(0, 0) = cosf(radAngle);
			mat(0, 1) = -sinf(radAngle);
			mat(1, 0) = sinf(radAngle);
			mat(1, 1) = cosf(radAngle);
			mat(2, 2) = 1;
			mat(3, 3) = 1;
		}
		inline void SetViewMatrix(const Vector3 EYE, const Vector3 AT, const Vector3 UP)
		{
			///Get u, v, n
			Vector3 u, v, n;
			n = EYE - AT;
			n = n.ConvertToUnitVector();

			u = CrossProduct(n, UP);
			u = u.ConvertToUnitVector();

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

			mat(0,0) = 1 / (tanf(radFovy / 2) *aspect);
			mat(1,1) = 1 / (tanf(radFovy / 2));
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
			Vector4 tempVec4( vec.x, vec.y, vec.z);

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
