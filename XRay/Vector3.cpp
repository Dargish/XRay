#include "Vector3.h"

#include <cmath>


Vector3::Vector3(
	float x_ /*= 0.0f*/,
	float y_ /*= 0.0f*/,
	float z_ /*= 0.0f*/) :
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

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
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

float Vector3::lengthSquared() const
{
	return x*x + y*y + z*z;
}

float Vector3::distance(const Vector3& other) const
{
	return (other - *this).length();
}

float Vector3::dot(const Vector3& other) const
{
	return x*other.x + y*other.y + z*other.z;
}

Vector3 Vector3::cross(const Vector3& other) const
{
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
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

Vector3 Vector3::normalized() const
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

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
	return os << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}
