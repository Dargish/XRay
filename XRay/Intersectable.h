#pragma once

#include "Ray.h"


class Intersectable
{
public:
	Intersectable();
	virtual ~Intersectable();

	virtual bool intersect(const Ray& ray, float& t) const = 0;
};

