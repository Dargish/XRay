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

	// Purely hit detection tests

	// How many rays intersect from 0.0f to 1.0f
	float shootRays(Ray& ray, float coneRadAngle, const Vector3& planeNormal = Vector3()) const;

	// True if the ray intersects
	bool shootRay(Ray& ray) const;

	// Evaluate surface colour on closest intersection
	RGBA traceRays(Ray& ray, float coneRadAngle, const Vector3& planeNormal = Vector3()) const;
	RGBA traceRay(Ray& ray) const;

	RGB lightAtPoint(const Vector3& position, const Vector3& normal) const;

private:
	void tracePixel(const Camera& camera, Image& image, size_t w, size_t h) const;

	ScenePtr m_scene;
	size_t m_raysPerPixel;
};

