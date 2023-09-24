#include "Vector3.h"

Vector3::Vector3() :x(0), y(0), z(0)
{
}

Vector3::Vector3(const float& x, const float& y, const float& z) : x(x), y(y), z(z)
{
}

Vector3::Vector3(const Vector3& other) : Vector3(other.x, other.y, other.z)
{
}

float Vector3::getX() const
{
	return x;
}

float Vector3::getY() const
{
	return y;
}

float Vector3::getZ() const
{
	return z;
}

void Vector3::setX(const float& val)
{
	x = val;
}

void Vector3::setY(const float& val)
{
	y = val;
}

void Vector3::setZ(const float& val)
{
	z = val;
}

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 v(v1);
	return v += v2;
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 v(v1);
	return v -= v2;
}

Vector3 operator*(const Vector3& v1, const float& f)
{
	Vector3 v(v1);
	return v *= f;
}

Vector3 operator/(const Vector3& v1, const float& f)
{
	Vector3 v(v1);
	return v /= f;
}

std::ostream& operator<<(std::ostream& out, const Vector3& vec)
{
	return out << vec.getX() << " " << vec.getY() << " " << vec.getZ();
}

Vector3 produitVectoriel(const Vector3& v1, const Vector3& v2)
{
	Vector3 resultat(
		v1.getY() * v2.getZ() - v1.getZ() - v2.getY(),
		v1.getZ() * v2.getX() - v1.getX() - v2.getZ(),
		v1.getX() * v2.getY() - v1.getY() - v2.getX()
	);
	return resultat;
}

Vector3 Vector3::getNormalised()
{
	return Vector3(*this) / getMagnitude();
}

float Vector3::getMagnitude()
{
	return sqrt(x * x + y * y + z * z);
}

Vector3& Vector3::operator+=(const Vector3& v2)
{
	x += v2.x;
	y += v2.y;
	z += v2.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v2)
{
	x -= v2.x;
	y -= v2.y;
	z -= v2.z;
	return *this;
}

Vector3& Vector3::operator*=(const float& f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

Vector3& Vector3::operator/=(const float& f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}
