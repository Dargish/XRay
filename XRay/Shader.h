#pragma once

#include "fwd.h"
#include "RGBA.h"
#include "Vector3.h"

#include <memory>


class Shader
{
public:
	virtual ~Shader() { };

	virtual RGBA shade(const Scene& scene, const Ray& ray, const Vector3& N) const = 0;
};
