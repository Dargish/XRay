#include "RayTracer.h"

#include <tbb/task_group.h>


RayTracer::RayTracer()
{

}

void RayTracer::traceImage(const Scene& scene, const Camera& camera, Image& image) const
{
	tbb::task_group group;

	auto tracePixel = [&](size_t w, size_t h)
	{
		Ray ray = camera.ray(image.x(w), image.y(h));
		Scene::RayIntersectionResult intersectionResult;
		if (scene.shootRay(ray, intersectionResult))
		{
			ImageLock lock(image);
			Image::Pixel& pixel = image.pixel(w, h);
			pixel.r = intersectionResult.distance;
			pixel.g = intersectionResult.distance;
			pixel.b = intersectionResult.distance;
			pixel.a = 1.0;
		}
	};

	for (size_t h = 0; h < image.height(); ++h)
	{
		for (size_t w = 0; w < image.width(); ++w)
		{
			group.run([w, h, &tracePixel] {tracePixel(w, h); });
		}
	}

	group.wait();
}
