#include "RayTracer.h"
#include "Scene.h"
#include "Camera.h"
#include "Image.h"
#include "Ray.h"
#include "Light.h"
#include "Shader.h"
#include "Intersectable.h"

#include <tbb/task_group.h>
#include <tbb/parallel_for.h>


RayTracer::RayTracer(const ScenePtr& scene_, size_t baseRayCount_ /*= 32*/) :
	m_scene(scene_), m_baseRayCount(baseRayCount_)
{

}

const ScenePtr& RayTracer::scene() const
{
	return m_scene;
}

size_t RayTracer::baseRayCount() const
{
	return m_baseRayCount;
}

void RayTracer::setBaseRayCount(size_t baseRayCount_)
{
	m_baseRayCount = baseRayCount_;
}


void RayTracer::traceImage(const Camera& camera, Image& image) const
{
	tbb::parallel_for(size_t(0), image.height(), [&](size_t h) {
		tbb::parallel_for(size_t(0), image.width(), [&](size_t w) {
			tracePixel(camera, image, w, h);
		});
	});
}

float RayTracer::shootRays(Ray& ray, float coneRadAngle, const Vector3& planeNormal /*= Vector3()*/) const
{
	size_t rayCount = (size_t)(m_baseRayCount * ray.rayMultiplier);
	if (coneRadAngle < 0.0001f || rayCount <= 1)
	{
		return shootRay(ray) ? 1.0f : 0.0f;
	}

	float result = 0.0f;
	Vector3 u, v;
	ray.direction.orthogonalVectors(u, v);

	bool reflectOffNormalPlane = planeNormal != Vector3();

	tbb::parallel_for(size_t(0), rayCount, [&](size_t r) {
		Ray thisRay(ray.origin);
		thisRay.direction = Vector3::RandomRay(ray.direction, u, v, coneRadAngle);
		// Check against normal plane to ensure rays don't shoot under the surface of it
		int limit = 50; // Make sure this doesn't go on forever
		while (reflectOffNormalPlane && planeNormal.dot(thisRay.direction) < 0.0f && --limit > 0)
		{
			// Just search for another random ray and hope it's above the surface
			thisRay.direction = Vector3::RandomRay(ray.direction, u, v, coneRadAngle);
		}
		if (m_scene->shootRay(thisRay))
		{
			result += 1.0f;
		}
	});

	result /= (float)rayCount;

	return result;
}

bool RayTracer::shootRay(Ray& ray) const
{
	return m_scene->shootRay(ray);
}

RGBA RayTracer::traceRays(Ray& ray, float coneRadAngle, const Vector3& planeNormal /*= Vector3()*/) const
{
	size_t rayCount = (size_t)(m_baseRayCount * ray.rayMultiplier);
	if (coneRadAngle < 0.0001f || rayCount <= 1)
	{
		return traceRay(ray);
	}

	Vector3 u, v;
	ray.direction.orthogonalVectors(u, v);

	bool reflectOffNormalPlane = planeNormal != Vector3();

	RGBA combined(0.0f, 0.0f, 0.0f, 0.0f);
	tbb::parallel_for(size_t(0), rayCount, [&](size_t r) {
		Ray thisRay(ray.origin);
		thisRay.direction = Vector3::RandomRay(ray.direction, u, v, coneRadAngle);
		// Check against normal plane to ensure rays don't shoot under the surface of it
		int limit = 50; // Make sure this doesn't go on forever
		while (reflectOffNormalPlane && planeNormal.dot(thisRay.direction) < 0.0f && --limit > 0)
		{
			// Just search for another random ray and hope it's above the surface
			thisRay.direction = Vector3::RandomRay(ray.direction, u, v, coneRadAngle);
		}
		thisRay.rayMultiplier = ray.rayMultiplier * 0.5f;
		Scene::RayIntersectionResult intersectionResult;
		if (m_scene->shootRay(thisRay, &intersectionResult))
		{
			if (intersectionResult.intersectable->shader())
			{
				combined += intersectionResult.intersectable->shader()->shade(*this, thisRay, intersectionResult.normal, m_scene->lights());
			}
			else
			{
				combined.a += 1.0;
			}
		}
	});
	combined /= (float)rayCount;
	return combined;
}

RGBA RayTracer::traceRay(Ray& ray) const
{
	RGBA result(0.0f, 0.0f, 0.0f, 0.0f);
	Scene::RayIntersectionResult intersectionResult;
	if (m_scene->shootRay(ray, &intersectionResult))
	{
		if (intersectionResult.intersectable->shader())
		{
			result = intersectionResult.intersectable->shader()->shade(*this, ray, intersectionResult.normal, m_scene->lights());
		}
		else
		{
			result.a = 1.0;
		}
	}
	return result;
}

void RayTracer::tracePixel(const Camera& camera, Image& image, size_t w, size_t h) const
{
	float x = image.x(w);
	float y = image.y(h);
	float dx = image.x(w + 1) - x;
	float dy = image.y(h + 1) - y;

	float fRandMax = float(RAND_MAX);

	RGBA result(0.0f, 0.0f, 0.0f, 0.0f);

	tbb::parallel_for(size_t(0), m_baseRayCount, [&](size_t r) {
		float randX = (float(std::rand()) / fRandMax) - 0.5f;
		float randY = (float(std::rand()) / fRandMax) - 0.5f;
		Ray ray = camera.ray(x + randX * dx, y + randY * dy);
		ray.rayMultiplier = 0.5f;
		result += traceRay(ray);
	});

	result /= (float)m_baseRayCount;

	ImageLock lock(image);
	image.pixel(w, h) = result;
}
