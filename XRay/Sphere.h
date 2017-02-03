#pragma once

#include "Intersectable.h"


class Sphere : public Intersectable
{
public:
	Vector3 centre;
	float radius;

	Sphere(Vector3 centre, float radius);

	virtual float intersect(const Ray& ray) const override;
};

