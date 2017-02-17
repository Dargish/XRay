#pragma once

#include "BRDF.h"

class DistributionGGX : public DistributionBRDF
{
public:
	virtual float operator()(const Geometry& geometry, float roughness) const override;
};