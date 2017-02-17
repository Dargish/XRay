#include "DiffuseOrenNayer.h"
#include "Math.h"


float DiffuseOrenNayer::operator()(const Geometry& geometry, float roughness) const
{
	float rough4 = std::powf(roughness, 4.0f);
	float c1 = 1.0f - ((rough4 * 0.5f) / (rough4 + 0.33f));
	float cosri = geometry.VoL - (geometry.NoV * geometry.NoL);
	float m = geometry.NoL;
	if (cosri >= 0.0f)
	{
		m = std::min(1.0f, geometry.NoL / geometry.NoV);
	}
	float c2 = ((0.45f * rough4) / (rough4 + 0.09f)) * cosri * m;
	return saturate(c1 + c2) * geometry.NoL;
}