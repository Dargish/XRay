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

	ShaderPtr shader(new ShaderLambert(RGB(1.0f, 0.5f, 1.0f), 0.25f));

	ScenePtr scene(new Scene);

	scene->addIntersectable<Sphere>(Vector3(-2.0f, -1.0f, -3.0f), 1.0f)->setShader(shader);
	scene->addIntersectable<Sphere>(Vector3(0.0f, 0.5f, 1.0f), 3.0f)->setShader(shader);
	scene->addIntersectable<Sphere>(Vector3(2.0f, -1.0f, -3.0f), 1.0f)->setShader(shader);

	Image image(800, 600);

	camera.setAspectRatio(image.aspectRatio());

	RayTracer rayTracer(scene, 16);

	rayTracer.traceImage(camera, image);

	PostProcessStack postProcessStack;
	//PostProcessToneMapPtr toneMap = postProcessStack.push<PostProcessToneMap>();

	postProcessStack.process(image);

	std::string renderpath = "C:\\Users\\sc\\Documents\\GitHub\\XRay\\render_with_lighting";
	//std::string renderpath = "E:\\GitHub\\XRay\\render";

	ImageWriterBMP writerBMP;
	writerBMP.writeImage(image, renderpath + ".bmp");

	ImageWriterTGA writerTGA;
	writerTGA.writeImage(image, renderpath + ".tga");

	std::cout << "Wrote render to " << renderpath << ".bmp" << std::endl;
	std::cout << "Wrote render to " << renderpath << ".tga" << std::endl;

	return 0;
}