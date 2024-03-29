#include "Vector3.h"
#include "Math.h"


Vector3::Vector3(
	float x_ /*= 0.0f*/,
	float y_ /*= 0.0f*/,
	float z_ /*= 0.0f*/) :
	x(x_), y(y_), z(z_)
{

}

bool Vector3::operator==(const Vector3& other) const
{
	return (
		fequals(x, other.x) &&
		fequals(y, other.y) &&
		fequals(z, other.z)
		);
}

bool Vector3::operator!=(const Vector3& other) const
{
	return (
		!fequals(x, other.x) ||
		!fequals(y, other.y) ||
		!fequals(z, other.z)
		);
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

Vector3 Vector3::reflect(const Vector3& normal) const
{
	float d = dot(normal);
	Vector3 r(*this);
	r -= normal * d * 2.0f;
	return r.normalize();
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

void Vector3::orthogonalVectors(Vector3& u, Vector3& v) const
{
	if (x < y)
	{
		if (x < z)
		{
			u = cross(Vector3(1, 0, 0));
		}
		else
		{
			u = cross(Vector3(0, 0, 1));
		}
	}
	else
	{
		if (y < z)
		{
			u = cross(Vector3(0, 1, 0));
		}
		else
		{
			u = cross(Vector3(0, 0, 1));
		}
	}
	v = cross(u);
}

Vector3 Vector3::randomRay(float coneRadAngle) const
{
	Vector3 u, v;
	orthogonalVectors(u, v);
	return RandomRay(*this, u, v, coneRadAngle);
}

Vector3 Vector3::RandomRay(const Vector3& a, const Vector3& u, const Vector3& v, float coneRadAngle)
{
	float fRandMax = float(RAND_MAX);
	float theta = (float(std::rand()) / fRandMax) * coneRadAngle;
	float phi = (float(std::rand()) / fRandMax) * PI_2F - PI_F;
	return (u * std::cosf(phi) + v * std::sinf(phi)) * std::sinf(theta) + (a * std::cosf(theta));
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
	return os << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}
