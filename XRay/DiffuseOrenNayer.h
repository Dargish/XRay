#pragma once

#include "BRDF.h"

class DiffuseOrenNayer : public DiffuseBRDF
{
public:
	virtual float operator()(const Geometry& geometry, float roughness) const override;
};