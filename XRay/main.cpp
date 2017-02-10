#define NOMINMAX

#include <string>
#include <vector>

#include <tbb/tbb.h>

#include "Camera.h"
#include "Sphere.h"
#include "Scene.h"
#include "Image.h"
#include "RayTracer.h"
#include "ShaderLambert.h"
#include "ImageWriterBMP.h"
#include "ImageWriterTGA.h"
#include "PostProcessToneMap.h"


int main()
{
	tbb::task_scheduler_init init;

	tbb::task_group group;

	Camera camera(Vector3(0.0f, 0.0f, -9.0f));

	ShaderPtr shader(new ShaderLambert(RGB(1.0f, 0.5f, 1.0f), 0.05f));

	Scene scene;

	scene.addIntersectable<Sphere>(Vector3(-2.0f, -1.0f, -2.0f), 1.0f)->setShader(shader);
	scene.addIntersectable<Sphere>(Vector3(0.0f, 0.5f, 1.0f), 3.0f)->setShader(shader);
	scene.addIntersectable<Sphere>(Vector3(2.0f, -1.0f, -2.0f), 1.0f)->setShader(shader);

	Image image(800, 600);

	camera.setAspectRatio(image.aspectRatio());

	RayTracer rayTracer;

	rayTracer.traceImage(scene, camera, image);

	PostProcessStack postProcessStack;
	//PostProcessToneMapPtr toneMap = postProcessStack.push<PostProcessToneMap>();

	postProcessStack.process(image);

	ImageWriterBMP writerBMP;
	std::string renderpathBMP = "E:\\GitHub\\XRay\\render.bmp";
	writerBMP.writeImage(image, renderpathBMP);

	ImageWriterTGA writerTGA;
	std::string renderpathTGA = "E:\\GitHub\\XRay\\render.tga";
	writerTGA.writeImage(image, renderpathTGA);


	std::cout << "Wrote render to " << renderpathBMP << std::endl;
	std::cout << "Wrote render to " << renderpathTGA << std::endl;

	return 0;
}