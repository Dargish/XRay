#include "LightDirectional.h"
#include "RayTracer.h"
#include "Scene.h"
#include "Ray.h"
#include "Math.h"


LightDirectional::LightDirectional(
	const Vector3& direction_,
	const RGBA& emission_,
	float rayMultiplier_ /*= 1*/,
	float shadowSoftness_ /*= 0.0f*/) :
	m_direction(direction_.normalized()),
	m_emission(emission_),
	m_rayMultiplier(rayMultiplier_),
	m_shadowSoftness(shadowSoftness_)
{
}

const Vector3& LightDirectional::direction() const
{
	return m_direction;
}

const RGBA& LightDirectional::emission() const
{
	return m_emission;
}

float LightDirectional::rayMultiplier() const
{
	return m_rayMultiplier;
}

float LightDirectional::shadowSoftness() const
{
	return m_shadowSoftness;
}

void LightDirectional::setDirection(const Vector3& direction_)
{
	m_direction = direction_;
}

void LightDirectional::setEmission(const RGBA& emission_)
{
	m_emission = emission_;
}

void LightDirectional::setRayMultiplier(float rayMultiplier_)
{
	m_rayMultiplier = rayMultiplier_;
}

void LightDirectional::setShadowSoftness(float shadowSoftness_)
{
	m_shadowSoftness = shadowSoftness_;
}

RGB LightDirectional::light(const RayTracer& rayTracer, const Vector3& position, const Vector3& normal, float rayMultiplier) const
{
	RGB light;
	float shadowMult = 1.0f;
	rayMultiplier *= m_rayMultiplier;
	if (rayMultiplier > 0.0f && m_shadowSoftness > FLT_EPSILON)
	{
		float coneRadAngle = m_shadowSoftness * PI_F * 0.5f;
		shadowMult = 1.0f - rayTracer.shootRays(Ray(position, -m_direction, rayMultiplier), coneRadAngle, normal);
	}
	else
	{
		if (rayTracer.shootRay(Ray(position, -m_direction)))
		{
			return light;
		}
	}
	float NoL = saturate(normal.dot(-m_direction));
	float lightMult = m_emission.a * NoL * shadowMult;
	light = RGB(
		m_emission.r * lightMult,
		m_emission.g * lightMult,
		m_emission.b * lightMult
	).saturate();
	return light;
}
