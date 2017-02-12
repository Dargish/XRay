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
	float rayMultiplier;
	float distance;

	Ray(
		const Vector3& origin = Vector3(0.0f, 0.0f, 0.0f),
		const Vector3& direction = Vector3(0.0f, 0.0f, 0.0f),
		float rayMultiplier = 1.0f,
		float distance = std::numeric_limits<float>::max()
	);

	friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
};
