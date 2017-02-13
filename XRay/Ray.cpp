#include "Ray.h"


Ray::Ray(
	const Vector3& origin_ /*= Vector3(0.0f, 0.0f, 0.0f)*/,
	const Vector3& direction_ /*= Vector3(0.0f, 0.0f, 0.0f)*/,
	float rayMultiplier_ /*= 0*/,
	float distance_ /*= std::numeric_limits<float>::max()*/
) :
	origin(origin_), direction(direction_.normalized()), rayMultiplier(rayMultiplier_), distance(distance_)
{

}

std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
	return os << "Ray(" << ray.origin << ", " << ray.direction << ")";
}
