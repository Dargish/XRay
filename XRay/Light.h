#pragma once

#include "fwd.h"
#include "RGB.h"


class Light
{
public:
	virtual ~Light() { }

	virtual RGB light(const RayTracer& rayTracer, const Vector3& position, const Vector3& normal) const = 0;
};

