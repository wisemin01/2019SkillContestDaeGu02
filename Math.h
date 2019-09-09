#pragma once
#include <random>

using ulong = unsigned long;
using uint = unsigned int;

struct Matrix;

template <typename _Ty>
_Ty Lerp(const _Ty& s, const _Ty& e, float t)
{
	return s + (e - s) * t;
}

struct Vector2
	: public D3DXVECTOR2
{
	Vector2() {};
	Vector2(CONST FLOAT* v) : D3DXVECTOR2(v) {}
	Vector2(CONST D3DXFLOAT16* v) : D3DXVECTOR2(v) {}
	Vector2(CONST D3DXVECTOR2& v) : D3DXVECTOR2(v.x, v.y) {}
	Vector2(FLOAT x, FLOAT y) : D3DXVECTOR2(x, y) {}

	Vector2 ToRadian();
	Vector2 ToDegree();
	void Normalize();

	float Length();
	float LengthSq();

	void TransformNormal(CONST Matrix& m);
	void TransformCoord(CONST Matrix& m);

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Two;
	static const Vector2 Left;
	static const Vector2 Right;

	static Vector2 Normalize(CONST Vector2& v);
	static float Length(CONST Vector2& v);
	static float LengthSq(CONST Vector2& v);
	static Vector2 Lerp(CONST Vector2& a, CONST Vector2& b, float s);
	static float Dot(CONST Vector2& v1, CONST Vector2& v2);
	static Vector2 CCW(CONST Vector2& v1, CONST Vector2& v2);
};

struct Vector3
	: public D3DXVECTOR3
{
	Vector3() {};
	Vector3(CONST FLOAT* v) : D3DXVECTOR3(v) {}
	Vector3(CONST D3DVECTOR& v) : D3DXVECTOR3(v) {}
	Vector3(CONST D3DXFLOAT16* v) : D3DXVECTOR3(v) {}
	Vector3(CONST D3DXVECTOR3& v) : D3DXVECTOR3(v.x, v.y, v.z) {}
	Vector3(FLOAT x, FLOAT y, FLOAT z) : D3DXVECTOR3(x, y, z) {}

	float ToRotationValue();

	Vector3 ToRadian();
	Vector3 ToDegree();
	void Normalize();

	float Length();
	float LengthSq();

	void TransformNormal(CONST Matrix& m);
	void TransformCoord(CONST Matrix& m);

	Vector3 operator*(const Vector3& other)
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	Vector3 operator*(float s)
	{
		return Vector3(x * s, y * s, z * s);
	}

	Vector3 operator*(const Vector3& other) const
	{
		return  Vector3(x * other.x, y * other.y, z * other.z);
	}

	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 Two;
	static const Vector3 Up;
	static const Vector3 Down;

	static Vector3 Normalize(CONST Vector3& v);
	static float Length(CONST Vector3& v);
	static float LengthSq(CONST Vector3& v);
	static Vector3 Lerp(CONST Vector3& a, CONST Vector3& b, float s);
	static float Dot(CONST Vector3& v1, CONST Vector3& v2);
	static Vector3 Cross(CONST Vector3& v1, CONST Vector3& v2);
	static Vector3 TransformNormal(CONST Vector3& v, CONST Matrix& m);
	static Vector3 TransformCoord(CONST Vector3& v, CONST Matrix& m);
	static Vector3 Abs(CONST Vector3& v);
	static Vector3 XFlip(CONST Vector3& v);
	static Vector3 YFlip(CONST Vector3& v);
	static Vector3 ZFlip(CONST Vector3& v);
};

struct Vector4
	: public D3DXVECTOR4
{
	Vector4() {};
	Vector4(CONST FLOAT* v) : D3DXVECTOR4(v) {}
	Vector4(CONST D3DXFLOAT16* v) : D3DXVECTOR4(v) {}
	Vector4(CONST D3DXVECTOR4& v) : D3DXVECTOR4(v) {}
	Vector4(CONST D3DVECTOR& xyz, FLOAT w) : D3DXVECTOR4(xyz, w) {}
	Vector4(FLOAT x, FLOAT y, FLOAT z, FLOAT w) : D3DXVECTOR4(x, y, z, w) {}

	static const Vector4 Zero;
};

struct Quaternion
	: public D3DXQUATERNION
{
	Quaternion() {}
	Quaternion(CONST FLOAT* v) : D3DXQUATERNION(v) {}
	Quaternion(CONST D3DXFLOAT16* v) : D3DXQUATERNION(v) {}
	Quaternion(FLOAT x, FLOAT y, FLOAT z, FLOAT w) : D3DXQUATERNION(x, y, z, w) {}

	static const Quaternion Identity;

	static Quaternion Rotation(float yaw, float pitch, float roll);
	static Quaternion Rotation(const Vector3& euler);
	static Quaternion Rotation(const Matrix& m);
	static Quaternion SLerp(const Quaternion& a, const Quaternion& b, float fs);
	static Vector3 ToAxisAngle(const Quaternion& q, float angle);
};

struct Matrix :
	public D3DXMATRIXA16
{
	Matrix() {}
	Matrix(CONST FLOAT* v) : D3DXMATRIXA16(v) {}
	Matrix(CONST D3DMATRIX& v) : D3DXMATRIXA16(v) {}
	Matrix(CONST D3DXFLOAT16* v) : D3DXMATRIXA16(v) {}
	Matrix(
		FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
		FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
		FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
		FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44)
		:
		D3DXMATRIXA16(
			_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44) {}

	static const Matrix IdentityNormal;
	static const Matrix IdentityCoord;

	static Matrix Translation(float x, float y, float z);
	static Matrix Translation(const Vector3& p);
	static Matrix Transpose(const Matrix& m);
	static Matrix RotationX(float x);
	static Matrix RotationY(float y);
	static Matrix RotationZ(float z);
	static Matrix RotationQuaternion(const Quaternion& q);
	static Matrix Scaling(float sx, float sy, float sz);
	static Matrix Scaling(const Vector3& s);
	static Matrix PerspectiveFovLH(float fovy, float aspect, float zn, float zf);
	static Matrix LookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up = Vector3::Up);
	static Matrix OrthoLH(float width, float height, float zn, float zf);
	static Matrix View2D(const Vector3& position, const Vector3& scale, float angle);
	static void Decompose(const Matrix& m, Vector3* outPos, Vector3* outScale, Quaternion* outRotation);
};

class Color : public D3DXCOLOR
{
public:
	Color() : D3DXCOLOR() {}
	Color(DWORD argb) : D3DXCOLOR() {}
	Color(CONST FLOAT* v) : D3DXCOLOR(v) {}
	Color(CONST D3DXFLOAT16* v) : D3DXCOLOR(v) {}
	Color(CONST D3DCOLORVALUE& v) : D3DXCOLOR(v) {}
	Color(CONST D3DXCOLOR& v) : D3DXCOLOR(v) {}
	Color(FLOAT r, FLOAT g, FLOAT b, FLOAT a) : D3DXCOLOR(r, g, b, a) {}

	static const Color Red;
	static const Color Orange;
	static const Color Yellow;
	static const Color Green;
	static const Color Blue;
	static const Color Violet;
	static const Color Black;
	static const Color White;
	static const Color Original;
};

struct Circle
{
public:
	Circle(const Vector3& center, float radius)
		: center(center), radius(radius) {}

	Vector3 center;
	float radius;

	static bool Intersect(const Circle& c1, const Circle& c2);
};

class Random
{
private:
	std::random_device m_RandomDevice;
	std::mt19937_64 m_MersenneTwister64;
public:
	Random() {
		m_MersenneTwister64 = std::mt19937_64(m_RandomDevice());
	}

	static Random& Instance()
	{
		static Random random;
		return random;
	}

	float Get(float min, float max)
	{
		uniform_real_distribution<float> range(min, max);

		return range(m_MersenneTwister64);
	}

	int Get(int min, int max)
	{
		uniform_int_distribution<int> range(min, max);

		return range(m_MersenneTwister64);
	}
};

ostream& operator << (ostream& os, const Vector2& value);
ostream& operator << (ostream& os, const Vector3& value);
ostream& operator << (ostream& os, const Vector4& value);
ostream& operator << (ostream& os, const Quaternion& value);
ostream& operator << (ostream& os, const Matrix& value);

bool			PointInRect(const RECT* rc, const Vector3* pt);
bool			IntersectRect(const RECT* rc1, const RECT* rc2);

std::string		SecondsToTimeStringA(float seconds);
std::wstring	SecondsToTimeStringW(float seconds);

