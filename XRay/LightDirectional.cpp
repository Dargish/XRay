#include "LightDirectional.h"


LightDirectional::LightDirectional(const Vector3& direction_, const RGB& emission_) :
	m_direction(direction_), m_emission(emission_)
{
}

const Vector3& LightDirectional::direction() const
{
	return m_direction;
}

const RGB& LightDirectional::emission() const
{
	return m_emission;
}

void LightDirectional::setDirection(const Vector3& direction_)
{
	m_direction = direction_;
}

void LightDirectional::setEmission(const RGB& emission_)
{
	m_emission = emission_;
}

RGB LightDirectional::light(const RayTracer& rayTracer, const Vector3& position, const Vector3& normal) const
{
	(void)rayTracer;
	(void)position;
	(void)normal;
	return m_emission;
}
