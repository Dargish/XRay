#pragma once

#include "Ray.h"


class Intersectable
{
public:
	Intersectable();
	virtual ~Intersectable();

	virtual float intersect(const Ray& ray) const = 0;
};

