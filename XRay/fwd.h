#pragma once

#include <memory>
#include <vector>


class Camera;
class EnvironmentMap;
class Image;
class ImageWriter;
class ImageWriterBMP;
class ImageWriterTGA;
class Intersectable;
class Light;
class LightDirectional;
class PostProcess;
class PostProcessToneMap;
class PostProcessGammaCorrect;
struct Ray;
class RayTracer;
struct RGB;
struct RGBA;
class Scene;
class Shader;
class ShaderBRDF;
class IntersectableSphere;
class Vector3;

typedef std::shared_ptr<Camera> CameraPtr;
typedef std::shared_ptr<EnvironmentMap> EnvironmentMapPtr;
typedef std::shared_ptr<Intersectable> IntersectablePtr;
typedef std::shared_ptr<Light> LightPtr;
typedef std::shared_ptr<PostProcess> PostProcessPtr;
typedef std::shared_ptr<PostProcessToneMap> PostProcessToneMapPtr;
typedef std::shared_ptr<PostProcessGammaCorrect> PostProcessGammaCorrectPtr;
typedef std::shared_ptr<Scene> ScenePtr;
typedef std::shared_ptr<Shader> ShaderPtr;

typedef std::vector<IntersectablePtr> IntersectablePtrs;
typedef std::vector<LightPtr> LightPtrs;
typedef std::vector<PostProcessPtr> PostProcessPtrs;
