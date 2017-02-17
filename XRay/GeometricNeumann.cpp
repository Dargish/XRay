#include "GeometricNeumann.h"

#include <algorithm>

float GeometricNeumann::operator()(const Geometry& geometry) const
{
	return (geometry.NoL * geometry.NoV) / std::max(geometry.NoL, geometry.NoV);
}