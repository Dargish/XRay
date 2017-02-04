#define NOMINMAX

#include <tbb/tbb.h>
#include <tbb/task_group.h>

#include "Camera.h"
#include "Sphere.h"
#include "Scene.h"


int main()
{
	//tbb::task_scheduler_init init;

	//tbb::task_group group;

	size_t width = 60;
	size_t height = 30;

	Camera camera(Vector3(0.0f, 0.0f, -9.0f));

	Scene scene;

	scene.addIntersectable<Sphere>(Vector3(-2.0f, -1.0f, -2.0f), 1.0f);
	scene.addIntersectable<Sphere>(Vector3(0.0f, 0.5f, 1.0f), 3.0f);
	scene.addIntersectable<Sphere>(Vector3(2.0f, -1.0f, -2.0f), 1.0f);
	
	for (size_t h = 0; h < height; ++h)
	{
		for (size_t w = 0; w < width; ++w)
		{
			float x = (((float(w) + 0.5f) / float(width)) * 2.0f) - 1.0f;
			float y = (((float(h) + 0.5f) / float(height)) * 2.0f) - 1.0f;

			Ray ray = camera.ray(x, y);

			Scene::RayIntersectionResult result;

			if (scene.shootRay(ray, result))
			{
				std::cout << int(result.distance);
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}

	return 0;
}