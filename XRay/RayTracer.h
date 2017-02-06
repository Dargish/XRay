#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Image.h"

class RayTracer
{
public:
	RayTracer();

	void traceImage(const Scene& scene, const Camera& camera, Image& image) const;
};

