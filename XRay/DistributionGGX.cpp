#include "DistributionGGX.h"
#include "Math.h"


float DistributionGGX::operator()(const Geometry& geometry, float roughness) const
{
	float rough4 = std::pow(roughness, 4.0f);
	float ds = (geometry.NoH * rough4 - geometry.NoH) * geometry.NoH + 1.0f;
	return rough4 / (PI_F * ds * ds);
}