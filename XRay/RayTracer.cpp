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


RayTracer::RayTracer(const ScenePtr& scene_, size_t raysPerPixel_ /*= 32*/) :
	m_scene(scene_), m_raysPerPixel(raysPerPixel_)
{

}

const ScenePtr& RayTracer::scene() const
{
	return m_scene;
}

size_t RayTracer::raysPerPixel() const
{
	return m_raysPerPixel;
}

void RayTracer::setRaysPerPixel(size_t raysPerPixel_)
{
	m_raysPerPixel = raysPerPixel_;
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
	float result = 0.0f;
	Vector3 u, v;
	ray.direction.orthogonalVectors(u, v);

	bool reflectOffNormalPlane = planeNormal != Vector3();

	tbb::parallel_for(size_t(0), ray.childCount, [&](size_t r) {
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

	result /= (float)ray.childCount;

	return result;
}

bool RayTracer::shootRay(Ray& ray) const
{
	return m_scene->shootRay(ray);
}

RGBA RayTracer::traceRays(Ray& ray, float coneRadAngle, const Vector3& planeNormal /*= Vector3()*/) const
{
	if (coneRadAngle < 0.0001f)
	{
		return traceRay(ray);
	}

	RGBA combined(0.0f, 0.0f, 0.0f, 0.0f);

	Vector3 u, v;
	ray.direction.orthogonalVectors(u, v);

	bool reflectOffNormalPlane = planeNormal != Vector3();

	tbb::parallel_for(size_t(0), ray.childCount, [&](size_t r) {
		Ray thisRay(ray.origin);
		thisRay.direction = Vector3::RandomRay(ray.direction, u, v, coneRadAngle);
		// Check against normal plane to ensure rays don't shoot under the surface of it
		int limit = 50; // Make sure this doesn't go on forever
		while (reflectOffNormalPlane && planeNormal.dot(thisRay.direction) < 0.0f && --limit > 0)
		{
			// Just search for another random ray and hope it's above the surface
			thisRay.direction = Vector3::RandomRay(ray.direction, u, v, coneRadAngle);
		}
		thisRay.childCount = ray.childCount;
		Scene::RayIntersectionResult intersectionResult;
		if (m_scene->shootRay(thisRay, &intersectionResult))
		{
			if (intersectionResult.intersectable->shader())
			{
				combined += intersectionResult.intersectable->shader()->shade(*this, thisRay, intersectionResult.normal);
			}
			else
			{
				combined.a += 1.0;
			}
		}
	});
	combined /= (float)ray.childCount;
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
			result = intersectionResult.intersectable->shader()->shade(*this, ray, intersectionResult.normal);
		}
		else
		{
			result.a = 1.0;
		}
	}
	return result;
}

RGB RayTracer::lightAtPoint(const Vector3& position, const Vector3& normal) const
{
	RGB result;
	Vector3 adjustedPosition = position + normal * FLT_EPSILON;
	for (const LightPtr& light : m_scene->lights())
	{
		result += light->light(*this, adjustedPosition, normal);
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

	tbb::parallel_for(size_t(0), m_raysPerPixel, [&](size_t r) {
		float randX = (float(std::rand()) / fRandMax) - 0.5f;
		float randY = (float(std::rand()) / fRandMax) - 0.5f;
		Ray ray = camera.ray(x + randX * dx, y + randY * dy);
		ray.childCount = m_raysPerPixel / 2;
		result += traceRay(ray);
	});

	result /= (float)m_raysPerPixel;

	ImageLock lock(image);
	image.pixel(w, h) = result;
}
