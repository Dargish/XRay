#include "ShaderLambert.h"
#include "Scene.h"
#include "Math.h"
#include "Ray.h"
#include "Light.h"
#include "RayTracer.h"

#include <algorithm>
#include <tbb/parallel_for.h>


ShaderLambert::ShaderLambert()
{

}

ShaderLambert::ShaderLambert(const RGB& diffuse_, float roughness_, const RGB& indexOfRefraction_) :
	m_diffuse(diffuse_), m_roughness(roughness_), m_indexOfRefraction(indexOfRefraction_)
{
	m_f0 = (m_indexOfRefraction - 1.0f) / (m_indexOfRefraction + 1.0f).pow(2.0f);
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

const RGB& ShaderLambert::indexOfRefraction() const
{
	return m_indexOfRefraction;
}

void ShaderLambert::setIndexOfRefraction(const RGB& indexOfRefraction_)
{
	m_indexOfRefraction = indexOfRefraction_;
	m_f0 = (m_indexOfRefraction - 1.0f) / (m_indexOfRefraction + 1.0f).pow(2.0f);
}

RGBA ShaderLambert::shade(const RayTracer& rayTracer, const Ray& ray, const Vector3& normal, const LightPtrs& lights) const
{
	Vector3 position = ray.origin + ray.direction * ray.distance + normal * 0.0001f;
	Vector3 reflect = ray.direction.reflect(normal);
	Vector3 V = -ray.direction;
	float NoV = normal.dot(V);

	RGB diffuseLight(0.0f, 0.0f, 0.0f);
	RGB specularLight(0.0f, 0.0f, 0.0f);
	for (const LightPtr& light : lights)
	{
		RGB lightEmission = light->light(rayTracer, position, ray.rayMultiplier);
		float diffuseFunction = 1.0f;
		if (light->hasDirection())
		{
			Vector3 L = light->direction(position);
			float VoL = V.dot(L);
			float NoL = normal.dot(L);
			Vector3 H = (V + L).normalized();
			float LoH = L.dot(H);
			float NoH = normal.dot(H);
			diffuseFunction = diffuseOrenNayer(VoL, NoL, NoV);
			RGB fresnelFunction = schlickFresnel(LoH).saturate();
			float geometricFunction = geometricNeumann(NoL, NoV);
			float distributionFunction = dGGX(NoH);
			RGB specular = fresnelFunction * geometricFunction * distributionFunction;
			specular /= 4.0f * NoL * NoV;
			specular *= lightEmission;
			specularLight += specular.saturate();
		}
		diffuseLight += (lightEmission * m_diffuse * diffuseFunction).saturate();
	}

	// Reflection
	RGBA reflection(0.0f, 0.0f, 0.0f, 0.0f);
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

	return (reflection * (1.0f - NoV)).saturate() + diffuseLight + specularLight;
}

float ShaderLambert::diffuseOrenNayer(float VoL, float NoL, float NoV) const
{
	float rough4 = std::powf(m_roughness, 4.0f);
	float c1 = 1.0f - ((rough4 * 0.5f) / (rough4 + 0.33f));
	float cosri = VoL - (NoV * NoL);
	float m = NoL;
	if (cosri >= 0.0f)
	{
		m = std::min(1.0f, NoL / NoV);
	}
	float c2 = ((0.45f * rough4) / (rough4 + 0.09f)) * cosri * m;
	return saturate(c1 + c2) * NoL;
}

RGB ShaderLambert::schlickFresnel(float LoH) const
{
	return m_f0 + (RGB(1.0f, 1.0f, 1.0f) - m_f0) * std::pow(1.0f - LoH, 5.0f);
}

float ShaderLambert::geometricNeumann(float NoL, float NoV) const
{
	return (NoL * NoV) / std::max(NoL, NoV);
}

float ShaderLambert::dGGX(float NoH) const
{
	float rough4 = std::pow(m_roughness, 4.0f);
	float ds = (NoH * rough4 - NoH) * NoH + 1.0f;
	return rough4 / (PI_F * ds * ds);
}
