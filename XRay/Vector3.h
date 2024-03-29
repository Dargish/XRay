#pragma once

#include <iostream>


class Vector3
{
public:
	float x, y, z;

	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-() const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3 operator*(float v) const;
	Vector3 operator/(float v) const;
	Vector3& operator*=(float v);
	Vector3& operator/=(float v);

	float length() const;

	float lengthSquared() const;

	float distance(const Vector3& other) const;

	float dot(const Vector3& other) const;

	Vector3 cross(const Vector3& other) const;

	Vector3 reflect(const Vector3& normal) const;

	Vector3& normalize();
	Vector3 normalized() const;

	void orthogonalVectors(Vector3& u, Vector3& v) const;

	Vector3 randomRay(float coneRadAngle) const;

	static Vector3 RandomRay(const Vector3& a, const Vector3& u, const Vector3& v, float coneRadAngle);

	friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};

