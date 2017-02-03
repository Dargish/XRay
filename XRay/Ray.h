#pragma once

#include "Vector3.h"


class Ray
{
public:
	Vector3 origin;
	Vector3 direction;

	Ray(
		const Vector3& origin = Vector3(0.0f, 0.0f, 0.0f),
		const Vector3& direction = Vector3(0.0f, 0.0f, 0.0f)
	);

	friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
};

