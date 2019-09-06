#include "DXUT.h"
#include "Math.h"

const Vector2 Vector2::Zero		= Vector2(0.0f, 0.0f);
const Vector2 Vector2::One		= Vector2(1.0f, 1.0f);
const Vector2 Vector2::Two		= Vector2(2.0f, 2.0f);
const Vector2 Vector2::Left		= Vector2(-1.0f, 0.0f);
const Vector2 Vector2::Right	= Vector2(1.0f, 0.0f);

const Vector3 Vector3::Zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::Two = Vector3(2.0f, 2.0f, 2.0f);
const Vector3 Vector3::Up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Down = Vector3(0.0f, -1.0f, 0.0f);

const Vector4 Vector4::Zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);

const Matrix Matrix::IdentityCoord = Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
const Matrix Matrix::IdentityNormal = Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0);

const Quaternion Quaternion::Identity = Quaternion(0, 0, 0, 0);

const Color Color::Red		= Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::Orange	= Color(1.0f, 0.49f, 0.0f, 1.0f);
const Color Color::Yellow	= Color(1.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Green	= Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Blue		= Color(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::Violet	= Color(0.78f, 0.08f, 0.52f, 1.0f);
const Color Color::Black	= Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::White	= Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::Original = Color(1.0f, 1.0f, 1.0f, 1.0f);

Vector3 Vector3::Normalize(const Vector3& v)
{
	Vector3 ret;
	D3DXVec3Normalize(&ret, &v);
	return ret;
}

float Vector3::Length(const Vector3& v)
{
	return D3DXVec3Length(&v);
}

float Vector3::LengthSq(const Vector3& v)
{
	return D3DXVec3LengthSq(&v);
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float s)
{
	Vector3 v;
	D3DXVec3Lerp(&v, &a, &b, s);
	return v;
}

float Vector3::Dot(const Vector3& v1, const Vector3& v2)
{
	return D3DXVec3Dot(&v1, &v2);
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 v;
	D3DXVec3Cross(&v, &v1, &v2);
	return v;
}

Vector3 Vector3::TransformNormal(const Vector3& v, const Matrix& m)
{
	Vector3 o;
	D3DXVec3TransformNormal(&o, &v, &m);

	return o;
}

Vector3 Vector3::TransformCoord(const Vector3& v, const Matrix& m)
{
	Vector3 o;
	D3DXVec3TransformCoord(&o, &v, &m);

	return o;
}

Vector3 Vector3::Abs(const Vector3& v)
{
	Vector3 ret;

	ret.x = fabsf(v.x);
	ret.y = fabsf(v.y);
	ret.z = fabsf(v.z);

	return ret;
}

Matrix Matrix::Translation(float x, float y, float z)
{
	Matrix m;
	D3DXMatrixTranslation(&m, x, y, z);
	return m;
}

Matrix Matrix::Translation(const Vector3& p)
{
	Matrix m;
	D3DXMatrixTranslation(&m, p.x, p.y, p.z);
	return m;
}

Matrix Matrix::Transpose(const Matrix& m)
{
	Matrix r;
	D3DXMatrixTranspose(&r, &m);
	return r;
}

Matrix Matrix::RotationX(float x)
{
	Matrix m;
	D3DXMatrixRotationX(&m, x);
	return m;
}

Matrix Matrix::RotationY(float y)
{
	Matrix m;
	D3DXMatrixRotationY(&m, y);
	return m;
}

Matrix Matrix::RotationZ(float z)
{
	Matrix m;
	D3DXMatrixRotationZ(&m, z);
	return m;
}

Matrix Matrix::RotationQuaternion(const Quaternion& q)
{
	Matrix m;
	D3DXMatrixRotationQuaternion(&m, &q);
	return m;
}

Matrix Matrix::Scaling(float sx, float sy, float sz)
{
	Matrix m;
	D3DXMatrixScaling(&m, sx, sy, sz);
	return m;
}

Matrix Matrix::Scaling(const Vector3& s)
{
	Matrix m;
	D3DXMatrixScaling(&m, s.x, s.y, s.z);
	return m;
}

Matrix Matrix::PerspectiveFovLH(float fovy, float aspect, float zn, float zf)
{
	Matrix m;
	D3DXMatrixPerspectiveFovLH(&m, fovy, aspect, zn, zf);
	return m;
}

Matrix Matrix::LookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up)
{
	Matrix m;
	D3DXMatrixLookAtLH(&m, &eye, &at, &up);
	return m;
}

Matrix Matrix::OrthoLH(float width, float height, float zn, float zf)
{
	Matrix m;
	D3DXMatrixOrthoLH(&m, width, height, zn, zf);
	return m;
}

Matrix Matrix::View2D(const Vector3& position, const Vector3& scale, float angle)
{
	return Matrix(scale.x * cosf(angle), scale.x * sinf(angle), 0, 0,
		-scale.y * sinf(angle), scale.y * cosf(angle), 0, 0,
		0, 0, scale.z, 0,
		-position.x * scale.y * cosf(angle) + position.y * scale.y * sinf(angle),
		-position.x * scale.x * sinf(angle) - position.y * scale.y * cosf(angle), 0, 1);
}

void Matrix::Decompose(const Matrix& m, Vector3* outPos, Vector3* outScale, Quaternion* outRotation)
{
	D3DXMatrixDecompose(outScale, outRotation, outPos, &m);
}

Quaternion Quaternion::Rotation(float yaw, float pitch, float roll)
{
	Quaternion q;
	D3DXQuaternionRotationYawPitchRoll(&q, yaw, pitch, roll);
	return q;
}

Quaternion Quaternion::Rotation(const Vector3& euler)
{
	Quaternion q;
	D3DXQuaternionRotationYawPitchRoll(&q, euler.y, euler.x, euler.z);
	return q;
}

Quaternion Quaternion::Rotation(const Matrix& m)
{
	Quaternion r;
	D3DXQuaternionRotationMatrix(&r, &m);
	return r;
}

Quaternion Quaternion::SLerp(const Quaternion& a, const Quaternion& b, float fs)
{
	Quaternion r;
	D3DXQuaternionSlerp(&r, &a, &b, fs);
	return r;
}

Vector3 Quaternion::ToAxisAngle(const Quaternion& q, float angle)
{
	Vector3 v;
	D3DXQuaternionToAxisAngle(&q, &v, &angle);
	return v;
}

Vector2 Vector2::Normalize(const Vector2& v)
{
	Vector2 _v;
	D3DXVec2Normalize(&_v, &v);
	return _v;
}

float Vector2::Length(const Vector2& v)
{
	return D3DXVec2Length(&v);
}

float Vector2::LengthSq(const Vector2& v)
{
	return D3DXVec2LengthSq(&v);
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float s)
{
	Vector2 v;
	D3DXVec2Lerp(&v, &a, &b, s);
	return v;
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2)
{
	return D3DXVec2Dot(&v1, &v2);
}

Vector2 Vector2::CCW(const Vector2& v1, const Vector2& v2)
{
	Vector2 v;
	D3DXVec2CCW(&v1, &v2);
	return v;
}

Vector3 Vector3::ToRadian()
{
	Vector3 ret;
	ret.x = D3DXToRadian(this->x);
	ret.y = D3DXToRadian(this->y);
	ret.z = D3DXToRadian(this->z);
	return ret;
}

Vector3 Vector3::ToDegree()
{
	Vector3 ret;
	ret.x = D3DXToDegree(this->x);
	ret.y = D3DXToDegree(this->y);
	ret.z = D3DXToDegree(this->z);
	return ret;
}

void Vector3::Normalize()
{
	D3DXVec3Normalize(this, this);
}

float Vector3::Length()
{
	return D3DXVec3Length(this);
}

float Vector3::LengthSq()
{
	return D3DXVec3LengthSq(this);
}

void Vector3::TransformNormal(const Matrix& m)
{
	D3DXVec3TransformNormal(this, this, &m);
}

void Vector3::TransformCoord(const Matrix& m)
{
	D3DXVec3TransformCoord(this, this, &m);
}

Vector2 Vector2::ToRadian()
{
	Vector2 ret;
	ret.x = D3DXToRadian(this->x);
	ret.y = D3DXToRadian(this->y);
	return ret;
}

Vector2 Vector2::ToDegree()
{
	Vector2 ret;
	ret.x = D3DXToDegree(this->x);
	ret.y = D3DXToDegree(this->y);
	return ret;
}

void Vector2::Normalize()
{
	D3DXVec2Normalize(this, this);
}

float Vector2::Length()
{
	return D3DXVec2Length(this);
}

float Vector2::LengthSq()
{
	return D3DXVec2LengthSq(this);
}

void Vector2::TransformNormal(const Matrix& m)
{
	D3DXVec2TransformNormal(this, this, &m);
}

void Vector2::TransformCoord(const Matrix& m)
{
	D3DXVec2TransformCoord(this, this, &m);
}

ostream& operator << (ostream& os, const Vector2& value)
{
	os << value.x << ", " << value.y;
	return os;
}

ostream& operator << (ostream& os, const Vector3& value)
{
	os << value.x << ", " << value.y << ", " << value.z;
	return os;
}

ostream& operator << (ostream& os, const Quaternion& value)
{
	os << value.x << ", " << value.y << ", " << value.z << ", " << value.w;
	return os;
}

ostream& operator<<(ostream& os, const Matrix& value)
{
	os << "[" << value._11 << ", " << value._12 << ", " << value._13 << ", " << value._14 << "]" << endl;
	os << "[" << value._21 << ", " << value._22 << ", " << value._23 << ", " << value._24 << "]" << endl;
	os << "[" << value._31 << ", " << value._32 << ", " << value._33 << ", " << value._34 << "]" << endl;
	os << "[" << value._41 << ", " << value._42 << ", " << value._43 << ", " << value._44 << "]";

	return os;
}

bool PointInRect(const RECT* rc, const Vector3* pt)
{
	return (
		rc->left <= pt->x && 
		rc->right >= pt->x &&
		rc->top <= pt->y &&
		rc->bottom >= pt->y
		);
}

std::string SecondsToTimeStringA(float seconds)
{
	int m = (int)seconds / 60;
	int s = (int)seconds % 60;

	return to_string(m) + ":" + to_string(s);
}

std::wstring SecondsToTimeStringW(float seconds)
{
	int m = (int)seconds / 60;
	int s = (int)seconds % 60;

	return to_wstring(m) + L":" + to_wstring(s);
}

ostream& operator << (ostream& os, const Vector4& value)
{
	os << value.x << ", " << value.y << ", " << value.z << ", " << value.w;
	return os;
}

bool Circle::Intersect(const Circle& c1, const Circle& c2)
{
	Vector3 v = c1.center - c2.center;

	float length = v.Length();
	float radiusSum = c1.radius + c2.radius;

	return (length <= radiusSum);
}
