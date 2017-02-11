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
		int sampleCount = 1,
		float shadowSoftness = 0.0f
	);

	const Vector3& direction() const;
	const RGBA& emission() const;
	int sampleCount() const;
	float shadowSoftness() const;

	void setDirection(const Vector3& direction);
	void setEmission(const RGBA& emission);
	void setSampleCount(int sampleCount);
	void setShadowSoftness(float shadowSoftness);

	virtual RGB light(const RayTracer& rayTracer, const Vector3& position, const Vector3& normal) const override;

private:
	Vector3 m_direction;
	RGBA m_emission;
	int m_sampleCount;
	float m_shadowSoftness;
};
