#pragma once

#include "BRDF.h"

class FresnelSchlick : public FresnelBRDF
{
public:
	virtual RGB operator()(const Geometry& geometry, const RGB& f0) const override;
};