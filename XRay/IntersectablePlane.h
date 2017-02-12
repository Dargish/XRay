#pragma once

#include "Intersectable.h"
#include "Vector3.h"


class IntersectablePlane : public Intersectable
{
public:
	Vector3 position;
	Vector3 normal;

	IntersectablePlane();

	virtual bool intersect(const Ray& ray, float& t, Vector3& normal) const override;
};

