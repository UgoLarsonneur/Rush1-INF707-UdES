#pragma once

#include <ostream>

class Vector3
{
public:
	Vector3();
	Vector3(const float& x, const float& zy, const float& z);
	Vector3(const Vector3& other);

	float getX() const;
	float getY() const;
	float getZ() const;

	void setX(const float& val);
	void setY(const float& val);
	void setZ(const float& val);


	Vector3 getNormalised();

	float getMagnitude();

	Vector3& operator+=(const Vector3& v2);
	Vector3& operator-=(const Vector3& v2);
	Vector3& operator*=(const float& f);
	Vector3& operator/=(const float& f);

private:

	float x;
	float y;
	float z;
};


Vector3 produitVectoriel(const Vector3& v1, const Vector3& v2);

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& v1, const float& f);
Vector3 operator/(const Vector3& v1, const float& f);

std::ostream& operator<<(std::ostream& out, const Vector3& vec);