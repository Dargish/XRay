#include "IntersectablePlane.h"
#include "Ray.h"


IntersectablePlane::IntersectablePlane(
	const Vector3& position_ /*= Vector3(0.0f, 0.0f, 0.0f)*/,
	const Vector3& normal_ /*= Vector3(0.0f, 1.0f, 0.0f)*/
) :
	position(position_),
	normal(normal_.normalized())
{

}

bool IntersectablePlane::intersect(const Ray& ray, float& t, Vector3& normal_) const
{
	float denom = ray.direction.dot(-normal);
	if (denom > FLT_EPSILON)
	{
		Vector3 offset = position - ray.origin;
		float t0 = offset.dot(-normal) / denom;
		if (t0 >= 0)
		{
			t = t0;
			normal_ = normal;
			return true;
		}
	}
	return false;
}