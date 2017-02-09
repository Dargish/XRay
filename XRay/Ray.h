#pragma once

#include "fwd.h"
#include "Vector3.h"

#include <limits>

#undef max


struct Ray
{
public:
	Vector3 origin;
	Vector3 direction;
	float distance;
	size_t childCount;

	Ray(
		const Vector3& origin = Vector3(0.0f, 0.0f, 0.0f),
		const Vector3& direction = Vector3(0.0f, 0.0f, 0.0f),
		float distance = std::numeric_limits<float>::max(),
		size_t childCount = 0
	);

	friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
};
