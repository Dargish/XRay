#include "IntersectableSphere.h"
#include "Ray.h"

#include <cmath>


IntersectableSphere::IntersectableSphere(
	const Vector3& center_ /*= Vector3(0.0f, 0.0f, 0.0f)*/,
	float radius_ /*= 1.0f*/
) :
	center(center_), radius(radius_)
{

}

bool IntersectableSphere::intersect(const Ray& ray, float& t, Vector3& normal) const
{
	Vector3 offset = ray.origin - center;

	float radiusSquared = radius * radius;

	float squaredDistance = offset.lengthSquared();

	if (squaredDistance < radiusSquared)
	{
		return false;
	}

	float a = 1.0f; //ray.direction.lengthSquared(); // Assume ray direction is normalised
	float b = 2.0f * ray.direction.dot(offset);
	float c = offset.lengthSquared() - radiusSquared;
		
	float d = (b*b) - (4.0f*a*c);
	
	if (d < 0.0f)
	{
		return false;
	}
	else
	{
		float sqrt_d = sqrt(d);
		float t0 = (-b - sqrt_d) / (2.0f * a);
		float t1 = (-b + sqrt_d) / (2.0f * a);

		if (t1 < 0.0f)
		{
			return false;
		}

		t = t0;
		normal = ((ray.origin + ray.direction * t) - center).normalize();

		return true;
	}
}
