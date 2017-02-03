#include "Ray.h"


Ray::Ray(
	const Vector3& origin_ /*= Vector3(0.0f, 0.0f, 0.0f)*/,
	const Vector3& direction_ /*= Vector3(0.0f, 0.0f, 0.0f)*/
) :
	origin(origin_), direction(direction_)
{

}

std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
	return os << "Ray(" << ray.origin << ", " << ray.direction << ")";
}
