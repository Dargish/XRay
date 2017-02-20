#include "DistributionGGX.h"
#include "Math.h"


float DistributionGGX::operator()(const Geometry& geometry, float roughness) const
{
	float rough4 = std::pow(roughness, 4.0f);
	float NoH2 = geometry.NoH * geometry.NoH;
	float ds = (NoH2 * (rough4 - 1.0f)) + 1.0f;
	return rough4 / (PI_F * ds * ds);
}