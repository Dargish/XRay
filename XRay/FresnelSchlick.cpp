#include "FresnelSchlick.h"

RGB FresnelSchlick::operator()(const Geometry& geometry, const RGB& f0) const
{
	return f0 + (RGB(1.0f, 1.0f, 1.0f) - f0) * std::pow(1.0f - geometry.LoH, 5.0f);
}