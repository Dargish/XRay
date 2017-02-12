#pragma once

#include "Light.h"
#include "RGBA.h"
#include "Vector3.h"


class LightDirectional : public Light
{
public:
	LightDirectional(
		const Vector3& direction,
		const RGBA& emission,
		float rayMultiplier = 0.5f,
		float shadowSoftness = 0.0f
	);

	const Vector3& direction() const;
	const RGBA& emission() const;
	float rayMultiplier() const;
	float shadowSoftness() const;

	void setDirection(const Vector3& direction);
	void setEmission(const RGBA& emission);
	void setRayMultiplier(float rayMultiplier);
	void setShadowSoftness(float shadowSoftness);

	virtual RGB light(const RayTracer& rayTracer, const Vector3& position, const Vector3& normal, float rayMultiplier) const override;

private:
	Vector3 m_direction;
	RGBA m_emission;
	float m_rayMultiplier;
	float m_shadowSoftness;
};
