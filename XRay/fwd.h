#pragma once

#include <memory>


class Camera;
class Image;
class ImageWriter;
class ImageWriterBMP;
class ImageWriterTGA;
class Intersectable;
class PostProcess;
class PostProcessToneMap;
struct Ray;
class RayTracer;
struct RGB;
struct RGBA;
class Scene;
class Shader;
class ShaderLambert;
class Sphere;
class Vector3;

typedef std::shared_ptr<Camera> CameraPtr;
typedef std::shared_ptr<Intersectable> IntersectablePtr;
typedef std::shared_ptr<PostProcess> PostProcessPtr;
typedef std::shared_ptr<Scene> ScenePtr;
typedef std::shared_ptr<Shader> ShaderPtr;
