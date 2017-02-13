#pragma once

#include "Intersectable.h"
#include "Vector3.h"


class IntersectablePlane : public Intersectable
{
public:
	Vector3 position;
	Vector3 normal;

	IntersectablePlane(
		const Vector3& position = Vector3(0.0f, 0.0f, 0.0f),
		const Vector3& normal = Vector3(0.0f, 1.0f, 0.0f)
	);

	virtual bool intersect(const Ray& ray, float& t, Vector3& normal) const override;
};

