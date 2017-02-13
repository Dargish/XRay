#pragma once

#include "Intersectable.h"
#include "Vector3.h"


class IntersectableSphere : public Intersectable
{
public:
	Vector3 center;
	float radius;

	IntersectableSphere(
		const Vector3& center = Vector3(0.0f, 0.0f, 0.0f),
		float radius = 1.0f
	);

	virtual bool intersect(const Ray& ray, float& t, Vector3& normal) const override;
};

