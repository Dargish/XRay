#include "Vector3.h"

#include <cmath>


Vector3::Vector3(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f) :
	x(x_), y(y_), z(z_)
{

}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3 Vector3::operator*(float v) const
{
	return Vector3(x * v, y * v, z * v);
}

Vector3 Vector3::operator/(float v) const
{
	return Vector3(x / v, y / v, z / v);
}

Vector3& Vector3::operator*=(float v)
{
	x *= v;
	y *= v;
	z *= v;
	return *this;
}

Vector3& Vector3::operator/=(float v)
{
	x /= v;
	y /= v;
	z /= v;
	return *this;
}

float Vector3::length() const
{
	return std::sqrtf(x*x + y*y + z*z);
}

float Vector3::dot(const Vector3& other) const
{
	return std::sqrtf(x*other.x + y*other.y + z*other.z);
}

Vector3& Vector3::normalize()
{
	float l = length();
	if (l != 0.0f)
	{
		x /= l;
		y /= l;
		z /= l;
	}
	return *this;
}

Vector3 Vector3::normalize() const
{
	float l = length();
	if (l != 0.0f)
	{
		return Vector3(x / l, y / l, z / l);
	}
	else
	{
		return Vector3(x, y, z);
	}
}

