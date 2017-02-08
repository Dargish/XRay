#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Image.h"

class RayTracer
{
public:
	RayTracer();

	size_t raysPerPixel() const;
	void setRaysPerPixel(size_t raysPerPixel);

	void traceImage(const Scene& scene, const Camera& camera, Image& image) const;

private:
	void tracePixel(const Scene& scene, const Camera& camera, Image& image, size_t w, size_t h) const;
	Image::Color traceRay(const Scene& scene, const Ray& ray) const;

	size_t m_raysPerPixel;
};

