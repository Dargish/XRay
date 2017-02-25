#include "EnvironmentMapLatLong.h"
#include "Math.h"

EnvironmentMapLatLong::EnvironmentMapLatLong(const std::wstring& filepath) :
	EnvironmentMap(filepath)
{

}

RGBA EnvironmentMapLatLong::sample(const Vector3& direction) const
{
	float u = (std::atanf(direction.x / direction.z) + PI_F) / PI_2F;
	float v = (std::asinf(direction.y) + HALF_PI_F) / PI_F;
	return m_image.sample(u, v);
}