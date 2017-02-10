#include "ShaderLambert.h"
#include "Scene.h"
#include "Math.h"
#include "Ray.h"
#include "RayTracer.h"

#include <algorithm>
#include <tbb/parallel_for.h>


ShaderLambert::ShaderLambert()
{

}

ShaderLambert::ShaderLambert(RGB diffuse_, float roughness_) :
	m_diffuse(diffuse_), m_roughness(roughness_)
{

}

const RGB& ShaderLambert::diffuse() const
{
	return m_diffuse;
}

void ShaderLambert::setDiffuse(const RGB& diffuse_)
{
	m_diffuse = diffuse_;
}

float ShaderLambert::roughness() const
{
	return m_roughness;
}

void ShaderLambert::setRoughness(float roughness_)
{
	m_roughness = roughness_;
}

RGBA ShaderLambert::shade(const RayTracer& rayTracer, const Ray& ray, const Vector3& normal) const
{
	Vector3 position = ray.origin + ray.direction * ray.distance;
	Vector3 reflect = ray.direction.reflect(normal);

	RGBA reflection(0.0f, 0.0f, 0.0f, 0.0f);

	RGB light = rayTracer.lightAtPoint(position, normal);
	RGBA diffuse = m_diffuse * light;

	// Reflection
	if (ray.childCount > 0)
	{
		Ray reflectRay(position, reflect);
		reflectRay.childCount = ray.childCount / 2;
		if (ray.childCount == 1)
		{
			reflection = rayTracer.traceRay(reflectRay);
		}
		else
		{
			// * 0.5f to limit to forward facing hemisphere
			float coneRadAngle = m_roughness * PI_F * 0.5f;
			reflection = rayTracer.traceRays(coneRadAngle, reflectRay, normal);
		}
	}

	float NoV = normal.dot(ray.direction);
	return (reflection * (1.0f + NoV) + diffuse * -NoV).saturate();
}
