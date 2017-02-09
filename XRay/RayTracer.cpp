#include "RayTracer.h"
#include "Scene.h"
#include "Camera.h"
#include "Image.h"
#include "Ray.h"
#include "Shader.h"
#include "Intersectable.h"

#include <tbb/task_group.h>
#include <tbb/parallel_for.h>


RayTracer::RayTracer() :
	m_raysPerPixel(8)
{

}

size_t RayTracer::raysPerPixel() const
{
	return m_raysPerPixel;
}

void RayTracer::setRaysPerPixel(size_t raysPerPixel_)
{
	m_raysPerPixel = raysPerPixel_;
}


void RayTracer::traceImage(const Scene& scene, const Camera& camera, Image& image) const
{
	tbb::parallel_for(size_t(0), image.height(), [&](size_t h) {
		tbb::parallel_for(size_t(0), image.width(), [&](size_t w) {
			tracePixel(scene, camera, image, w, h);
		});
	});
}

void RayTracer::tracePixel(const Scene& scene, const Camera& camera, Image& image, size_t w, size_t h) const
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
		result += traceRay(scene, ray);
	});

	result /= (float)m_raysPerPixel;

	ImageLock lock(image);
	image.pixel(w, h) = result;
}

RGBA RayTracer::traceRay(const Scene& scene, Ray& ray) const
{
	RGBA result(0.0f, 0.0f, 0.0f, 0.0f);
	Scene::RayIntersectionResult intersectionResult;
	if (scene.shootRay(ray, intersectionResult))
	{
		if (intersectionResult.intersectable->shader())
		{
			Vector3 P = ray.origin + ray.direction * ray.distance;
			result = intersectionResult.intersectable->shader()->shade(scene, ray, P, intersectionResult.normal);
		}
		else
		{
			result.a = 1.0;
		}
	}
	return result;
}
