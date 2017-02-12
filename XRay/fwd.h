#pragma once

#include <memory>


class Camera;
class Image;
class ImageWriter;
class ImageWriterBMP;
class ImageWriterTGA;
class Intersectable;
class Light;
class LightDirectional;
class PostProcess;
class PostProcessToneMap;
struct Ray;
class RayTracer;
struct RGB;
struct RGBA;
class Scene;
class Shader;
class ShaderLambert;
class IntersectableSphere;
class Vector3;

typedef std::shared_ptr<Camera> CameraPtr;
typedef std::shared_ptr<Intersectable> IntersectablePtr;
typedef std::shared_ptr<Light> LightPtr;
typedef std::shared_ptr<PostProcess> PostProcessPtr;
typedef std::shared_ptr<Scene> ScenePtr;
typedef std::shared_ptr<Shader> ShaderPtr;
