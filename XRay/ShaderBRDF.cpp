#include "ShaderBRDF.h"
#include "Scene.h"
#include "Math.h"
#include "Ray.h"
#include "Light.h"
#include "RayTracer.h"

#include <algorithm>
#include <tbb/parallel_for.h>


ShaderBRDF::ShaderBRDF(const BRDFSetPtr& brdfSet) :
	m_brdfSet(brdfSet)
{

}

ShaderBRDF::ShaderBRDF(const BRDFSetPtr& brdfSet, const RGB& diffuse_, float roughness_, const RGB& f0_) :
	m_brdfSet(brdfSet), m_diffuse(diffuse_), m_roughness(roughness_), m_f0(f0_)
{

}

const RGB& ShaderBRDF::diffuse() const
{
	return m_diffuse;
}

void ShaderBRDF::setDiffuse(const RGB& diffuse_)
{
	m_diffuse = diffuse_;
}

float ShaderBRDF::roughness() const
{
	return m_roughness;
}

void ShaderBRDF::setRoughness(float roughness_)
{
	m_roughness = roughness_;
}

const RGB& ShaderBRDF::f0() const
{
	return m_f0;
}

void ShaderBRDF::setF0(const RGB& f0_)
{
	m_f0 = f0_;
}

RGBA ShaderBRDF::shade(const RayTracer& rayTracer, const Ray& ray, const Vector3& normal, const LightPtrs& lights) const
{
	if (!m_brdfSet)
	{
		return m_diffuse;
	}

	Vector3 position = ray.origin + ray.direction * ray.distance + normal * 0.0001f;
	Vector3 V = -ray.direction;

	RGB diffuseLight(0.0f, 0.0f, 0.0f);
	RGB specularLight(0.0f, 0.0f, 0.0f);
	for (const LightPtr& light : lights)
	{
		RGB lightEmission = light->light(rayTracer, position, ray.rayMultiplier);
		float diffuseFunction = 1.0f;
		if (light->hasDirection())
		{
			Vector3 L = light->direction(position);
			BRDF::Geometry lightGeometry(normal, V, L);
			diffuseFunction = m_brdfSet->diffuse(lightGeometry, m_roughness);
			RGB specular = m_brdfSet->specular(lightGeometry, m_roughness, m_f0);
			specular *= lightEmission;
			specularLight += specular.saturate();
		}
		diffuseLight += (lightEmission * m_diffuse * diffuseFunction).saturate();
	}

	// Reflection
	RGBA reflection(0.0f, 0.0f, 0.0f, 0.0f);
	Vector3 reflect = ray.direction.reflect(normal);
	size_t rayCount = (size_t)(rayTracer.baseRayCount() * ray.rayMultiplier);
	if (rayCount > 0)
	{
		Ray reflectRay(position, reflect, ray.rayMultiplier * 0.5f);
		if (rayCount == 1)
		{
			reflection = rayTracer.traceRay(reflectRay);
		}
		else
		{
			// * 0.5f to limit to forward facing hemisphere
			float coneRadAngle = m_roughness * PI_F * 0.5f;
			reflection = rayTracer.traceRays(reflectRay, coneRadAngle, normal);
		}
	}
	BRDF::Geometry reflectGeometry(normal, V, reflect);
	RGB specular = (*m_brdfSet->fresnelBRDF())(reflectGeometry, m_roughness);
	reflection *= specular;
	return reflection + diffuseLight + specularLight;
}
