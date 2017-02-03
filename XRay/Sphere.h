#pragma once

#include "Intersectable.h"


class Sphere : public Intersectable
{
public:
	Vector3 center;
	float radius;

	Sphere(
		Vector3 center = Vector3(0.0f, 0.0f, 0.0f),
		float radius = 1.0f
	);

	virtual bool intersect(const Ray& ray, float& t) const override;
};

