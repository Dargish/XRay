#include "Sphere.h"

#include <limits>


Sphere::Sphere(Vector3 centre_, float radius_) :
	centre(centre_), radius(radius_)
{

}

float Sphere::intersect(const Ray& ray) const
{
	Vector3 v = centre - ray.origin;
	if (v.length() < radius)
	{
		// Ray origin is inside the sphere
		return std::numeric_limits<float>::max();
	}
	float DoV = ray.direction.dot(v);
	if (DoV < 0.0f)
	{
		// Sphere is behind the ray
		return std::numeric_limits<float>::max();
	}

	Vector3 closestPoint = ray.origin - ray.direction * DoV;
}
