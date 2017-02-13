#pragma once

#include "fwd.h"
#include "RGBA.h"


class Shader
{
public:
	virtual ~Shader() { };

	virtual RGBA shade(const RayTracer& rayTracer, const Ray& ray, const Vector3& normal, const LightPtrs& lights) const = 0;
};
