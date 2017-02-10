#pragma once

#include "Light.h"
#include "Vector3.h"


class LightDirectional : public Light
{
public:
	LightDirectional(const Vector3& direction, const RGB& emission);

	const Vector3& direction() const;
	const RGB& emission() const;

	void setDirection(const Vector3& direction);
	void setEmission(const RGB& emission);

	virtual RGB light(const RayTracer& rayTracer, const Vector3& position, const Vector3& normal) const override;

private:
	Vector3 m_direction;
	RGB m_emission;
};
