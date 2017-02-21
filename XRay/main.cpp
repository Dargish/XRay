#define NOMINMAX

#include <string>
#include <vector>

#include <tbb/tbb.h>

#include "Camera.h"
#include "IntersectableSphere.h"
#include "IntersectablePlane.h"
#include "Scene.h"
#include "Image.h"
#include "RayTracer.h"
#include "ShaderBRDF.h"
#include "LightDirectional.h"
#include "ImageWriterBMP.h"
#include "ImageWriterTGA.h"
#include "ImageWriterEXR.h"
#include "PostProcessGammaCorrect.h"

#include "DiffuseOrenNayer.h"
#include "FresnelSchlick.h"
#include "GeometricNeumann.h"
#include "DistributionGGX.h"

#include <chrono>
typedef std::chrono::high_resolution_clock Clock;


typedef TypedBRDFSet<DiffuseOrenNayer, FresnelSchlick, GeometricNeumann, DistributionGGX> StandardBRDF;


int main()
{
	auto t1 = Clock::now();

	int numThreads = tbb::task_scheduler_init::default_num_threads();

	std::cout << "Rendering using " << numThreads << " cores" << std::endl;

	tbb::task_scheduler_init init(numThreads);

	tbb::task_group group;

	Camera camera(Vector3(0.0f, 2.5f, -12.0f) , Vector3(0.0f, -0.05f, 0.9f));

	BRDFSetPtr brdfSet(new StandardBRDF);

	ShaderPtr yellowShader(new ShaderBRDF(brdfSet, RGB(0.9f, 0.9f, 0.2f), 0.25f, RGB(0.04f)));
	ShaderPtr greenShader(new ShaderBRDF(brdfSet, RGB(0.2f, 0.9f, 0.2f), 0.25f, RGB(0.04f)));
	ShaderPtr blueShader(new ShaderBRDF(brdfSet, RGB(0.2f, 0.2f, 0.9f), 0.25f, RGB(0.04f)));
	ShaderPtr planeShader(new ShaderBRDF(brdfSet, RGB(0.5f, 0.5f, 0.5f), 0.01f, RGB(0.04f)));
	ShaderPtr goldShader(new ShaderBRDF(brdfSet, RGB(0.0f, 0.0f, 0.0f), 0.01f, RGB(1.0f, 0.71f, 0.29f)));

	ScenePtr scene(new Scene);

	scene->addLight<LightDirectional>(Vector3(-0.5f, -0.5f, 1.0f), RGBA(1.0f, 1.0f, 1.0f, 2.0f), 0.5f, 0.05f);

	scene->addIntersectable<IntersectableSphere>(Vector3(-2.0f, 0.5f, -3.0f), 1.0f)->setShader(yellowShader);
	scene->addIntersectable<IntersectableSphere>(Vector3(0.0f, 3.0f, 1.0f), 3.0f)->setShader(greenShader);
	scene->addIntersectable<IntersectableSphere>(Vector3(2.5f, 2.5f, -5.0f), 1.0f)->setShader(goldShader);
	scene->addIntersectable<IntersectablePlane>(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f))->setShader(planeShader);

	Image image(800, 600);

	camera.setAspectRatio(image.aspectRatio());

	RayTracer rayTracer(scene, 16);

	rayTracer.traceImage(camera, image);

	PostProcessStack postProcessStack;
	postProcessStack.push<PostProcessGammaCorrect>();
	postProcessStack.process(image);

	//std::string renderpath = "C:\\Users\\sc\\Documents\\GitHub\\XRay\\render";
	std::string renderpath = "E:\\GitHub\\XRay\\render";

	ImageWriterBMP writerBMP;
	writerBMP.writeImage(image, renderpath + ".bmp");

	ImageWriterTGA writerTGA;
	writerTGA.writeImage(image, renderpath + ".tga");

	ImageWriterEXR writerEXR;
	writerEXR.writeImage(image, renderpath + ".exr");

	std::cout << "Wrote render to " << renderpath << ".bmp" << std::endl;
	std::cout << "Wrote render to " << renderpath << ".tga" << std::endl;
	std::cout << "Wrote render to " << renderpath << ".exr" << std::endl;

	auto t2 = Clock::now();
	std::cout << "Render time: "
		<< double(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()) / 1000.0
		<< " seconds" << std::endl;

	return 0;
}