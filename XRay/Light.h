#pragma once

#include "fwd.h"
#include "RGB.h"


class Light
{
public:
	virtual ~Light() { }

	// Does the light have direction? Example: Ambient doesn't
	virtual bool hasDirection() const = 0;

	// Direction of the light from the given position
	virtual Vector3 direction(const Vector3& position) const = 0;

	// The amount of lighting reaching the given position
	virtual RGB light(const RayTracer& rayTracer, const Vector3& position, float rayMultiplier) const = 0;
};

