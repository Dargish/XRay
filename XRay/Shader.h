#pragma once

#include "fwd.h"
#include "RGBA.h"

#include <memory>


class Shader
{
public:
	virtual ~Shader() { };

	virtual RGBA shade(const RayTracer& rayTracer, const Ray& ray, const Vector3& normal) const = 0;
};
