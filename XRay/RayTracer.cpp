#include "RayTracer.h"

#include <tbb/task_group.h>
#include <tbb/parallel_for.h>


RayTracer::RayTracer() :
	m_raysPerPixel(64)
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

	Image::Color result;

	tbb::parallel_for(size_t(0), m_raysPerPixel, [&](size_t r) {
		float randX = (float(std::rand()) / fRandMax) - 0.5f;
		float randY = (float(std::rand()) / fRandMax) - 0.5f;
		Ray ray = camera.ray(x + randX * dx, y + randY * dy);
		result += traceRay(scene, ray);
	});

	result /= (float)m_raysPerPixel;

	ImageLock lock(image);
	image.pixel(w, h) = result;
}

Image::Color RayTracer::traceRay(const Scene& scene, const Ray& ray) const
{
	Image::Color result;
	Scene::RayIntersectionResult intersectionResult;
	if (scene.shootRay(ray, intersectionResult))
	{
		result.r = intersectionResult.distance;
		result.g = intersectionResult.distance;
		result.b = intersectionResult.distance;
		result.a = 1.0;
	}
	return result;
}
