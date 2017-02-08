#define NOMINMAX

#include <string>
#include <vector>

#include <tbb/tbb.h>

#include "Camera.h"
#include "Sphere.h"
#include "Scene.h"
#include "Image.h"
#include "RayTracer.h"
#include "ImageWriterBMP.h"
#include "ImageWriterTGA.h"
#include "PostProcessToneMap.h"


int main()
{
	tbb::task_scheduler_init init;

	tbb::task_group group;

	Camera camera(Vector3(0.0f, 0.0f, -9.0f));

	Scene scene;

	scene.addIntersectable<Sphere>(Vector3(-2.0f, -1.0f, -2.0f), 1.0f);
	scene.addIntersectable<Sphere>(Vector3(0.0f, 0.5f, 1.0f), 3.0f);
	scene.addIntersectable<Sphere>(Vector3(2.0f, -1.0f, -2.0f), 1.0f);

	Image image(800, 600);

	camera.setAspectRatio(image.aspectRatio());

	RayTracer rayTracer;

	rayTracer.traceImage(scene, camera, image);

	PostProcessStack postProcessStack;
	PostProcessToneMapPtr toneMap = postProcessStack.push<PostProcessToneMap>();

	postProcessStack.process(image);

	ImageWriterBMP writer;

	std::string renderpath = "E:\\GitHub\\XRay\\render.bmp";

	writer.writeImage(image, renderpath);

	std::cout << "Wrote render to " << renderpath << std::endl;

	return 0;
}