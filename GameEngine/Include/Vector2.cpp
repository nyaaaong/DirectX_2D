#include "Vector2.h"

Vector2::Vector2() :
	x(0.f),
	y(0.f)
{
}

Vector2::Vector2(float _x, float _y) :
	x(_x),
	y(_y)
{
}

Vector2::Vector2(const Vector2& v) :
	x(v.x),
	y(v.y)
{
}

Vector2::Vector2(const XMVECTOR& v)	:
	x(0.f),
	y(0.f)
{
	// XMVECTOR�� Vector2�� x�� y�� �˸´� ���� �־���
	XMStoreFloat2((XMFLOAT2*)this, v);
}

Vector2& Vector2::operator=(const Vector2& v)
{
	x = v.x;
	y = v.y;

	return *this;
}

Vector2& Vector2::operator=(const XMVECTOR& v)
{
	XMStoreFloat2((XMFLOAT2*)this, v);

	return *this;
}

Vector2& Vector2::operator=(float f)
{
	x = f;
	y = f;

	return *this;
}

bool Vector2::operator==(const Vector2& v) const
{
	return x == v.x && y == v.y;
}

bool Vector2::operator==(const XMVECTOR& v) const
{
	Vector2	v1;
	// v�� Vector2�� x, y�� ��ȯ��
	XMStoreFloat2((XMFLOAT2*)&v1, v);

	return x == v1.x && y == v1.y;
}

bool Vector2::operator!=(const Vector2& v) const
{
	return x != v.x || y != v.y;
}

bool Vector2::operator!=(const XMVECTOR& v) const
{
	Vector2	v1;
	XMStoreFloat2((XMFLOAT2*)&v1, v);

	return x != v1.x || y != v1.y;
}

float& Vector2::operator[](int Index)
{
	if (Index < 0 || Index > 1)
	{
		assert(false);
	}

	if (Index == 0)
		return x;

	return y;
}

// +
Vector2 Vector2::operator+(const Vector2& v) const
{
	XMVECTOR	v1 = Convert();
	XMVECTOR	v2 = v.Convert();

	return Vector2(v1 + v2);
}

Vector2 Vector2::operator+(const XMVECTOR& v) const
{
	return Vector2(Convert() + v);
}

Vector2 Vector2::operator+(const float f) const
{
	return Vector2(x + f, y + f);
}

// +=
Vector2 Vector2::operator+=(const Vector2& v)
{
	XMVECTOR	v1 = Convert();
	XMVECTOR	v2 = v.Convert();

	Convert(v1 + v2);

	return *this;
}

Vector2 Vector2::operator+=(const XMVECTOR& v)
{
	XMVECTOR	v1 = Convert();

	Convert(v1 + v);

	return *this;
}

Vector2 Vector2::operator+=(const float f)
{
	x += f;
	y += f;

	return *this;
}

// -
Vector2 Vector2::operator-(const Vector2& v) const
{
	XMVECTOR	v1 = Convert();
	XMVECTOR	v2 = v.Convert();

	return Vector2(v1 - v2);
}

Vector2 Vector2::operator-(const XMVECTOR& v) const
{
	return Vector2(Convert() - v);
}

Vector2 Vector2::operator-(const float f) const
{
	return Vector2(x - f, y - f);
}

// -=
Vector2 Vector2::operator-=(const Vector2& v)
{
	XMVECTOR	v1 = Convert();
	XMVECTOR	v2 = v.Convert();

	Convert(v1 - v2);

	return *this;
}

Vector2 Vector2::operator-=(const XMVECTOR& v)
{
	XMVECTOR	v1 = Convert();

	Convert(v1 - v);

	return *this;
}

Vector2 Vector2::operator-=(const float f)
{
	x -= f;
	y -= f;

	return *this;
}

// *
Vector2 Vector2::operator*(const Vector2& v) const
{
	XMVECTOR	v1 = Convert();
	XMVECTOR	v2 = v.Convert();

	return Vector2(v1 * v2);
}

Vector2 Vector2::operator*(const XMVECTOR& v) const
{
	return Vector2(Convert() * v);
}

Vector2 Vector2::operator*(const float f) const
{
	return Vector2(x * f, y * f);
}

// *=
Vector2 Vector2::operator*=(const Vector2& v)
{
	XMVECTOR	v1 = Convert();
	XMVECTOR	v2 = v.Convert();

	Convert(v1 * v2);

	return *this;
}

Vector2 Vector2::operator*=(const XMVECTOR& v)
{
	XMVECTOR	v1 = Convert();

	Convert(v1 * v);

	return *this;
}

Vector2 Vector2::operator*=(const float f)
{
	x *= f;
	y *= f;

	return *this;
}

// /
Vector2 Vector2::operator/(const Vector2& v) const
{
	XMVECTOR	v1 = Convert();
	XMVECTOR	v2 = v.Convert();

	return Vector2(v1 / v2);
}

Vector2 Vector2::operator/(const XMVECTOR& v) const
{
	return Vector2(Convert() / v);
}

Vector2 Vector2::operator/(const float f) const
{
	return Vector2(x / f, y / f);
}

// /=
Vector2 Vector2::operator/=(const Vector2& v)
{
	XMVECTOR	v1 = Convert();
	XMVECTOR	v2 = v.Convert();

	Convert(v1 / v2);

	return *this;
}

Vector2 Vector2::operator/=(const XMVECTOR& v)
{
	XMVECTOR	v1 = Convert();

	Convert(v1 / v);

	return *this;
}

Vector2 Vector2::operator/=(const float f)
{
	x /= f;
	y /= f;

	return *this;
}

Vector2 Vector2::operator++()
{
	x += 1.f;
	y += 1.f;

	return *this;
}

Vector2 Vector2::operator++(int)
{
	x += 1.f;
	y += 1.f;

	return *this;
}

Vector2 Vector2::operator--()
{
	x -= 1.f;
	y -= 1.f;

	return *this;
}

Vector2 Vector2::operator--(int)
{
	x -= 1.f;
	y -= 1.f;

	return *this;
}

float Vector2::Length() const
{
	return XMVectorGetX(XMVector2Length(Convert()));
}

float Vector2::Distance(const Vector2& v) const
{
	Vector2	Dist = v - *this;

	return Dist.Length();
}

void Vector2::Normalize()
{
	*this = XMVector2Normalize(Convert());
}

float Vector2::Dot(const Vector2& v) const
{
	return XMVectorGetX(XMVector2Dot(Convert(), v.Convert()));
}

float Vector2::Angle(const Vector2& v) const
{
	return 0.0f;
}

XMVECTOR Vector2::Convert()	const
{
	// Vector2�� XMFLOAT2�� ��ȯ�� ��ȯ
	return XMLoadFloat2((XMFLOAT2*)this);
}

void Vector2::Convert(const XMVECTOR& v)
{
	// v�� x y���� ���� Vector2�� x y������ ��ȯ
	XMStoreFloat2((XMFLOAT2*)this, v);
}
