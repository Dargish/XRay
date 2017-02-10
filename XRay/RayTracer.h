#pragma once

#include "fwd.h"
#include "Vector3.h"

class RayTracer
{
public:
	RayTracer(const ScenePtr& scene, size_t raysPerPixel = 32);

	const ScenePtr& scene() const;

	size_t raysPerPixel() const;
	void setRaysPerPixel(size_t raysPerPixel);

	void traceImage(const Camera& camera, Image& image) const;

	RGBA traceRays(float coneRadAngle, Ray& ray, const Vector3& planeNormal = Vector3()) const;
	RGBA traceRay(Ray& ray) const;

	RGB lightAtPoint(const Vector3& position, const Vector3& normal) const;

private:
	void tracePixel(const Camera& camera, Image& image, size_t w, size_t h) const;

	ScenePtr m_scene;
	size_t m_raysPerPixel;
};

