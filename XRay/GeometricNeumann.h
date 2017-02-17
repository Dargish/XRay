#pragma once

#include "BRDF.h"

class GeometricNeumann : public GeometricBRDF
{
public:
	virtual float operator()(const Geometry& geometry) const override;
};